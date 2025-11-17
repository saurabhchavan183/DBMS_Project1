/* slotted/slotted.c */
#include <stdio.h>
#include <string.h>
#include "slotted.h"
#include "pf.h" /* Use the PF layer */

/* ... (S_CreateFile, S_OpenFile, etc. would just call PF layer) ... */

int S_InsertRecord(int fileDesc, char *record, int length, RID *newRid) {
    int pagenum = -1;
    char *pagebuf;
    SlottedPageHeader *header;
    Slot *newSlot;
    int error;

    /* 1. Find a page with enough space. 
       (A real implementation would have a free-space list. 
       We'll do a simple sequential scan of pages.) */
    
    while ((error = PF_GetNextPage(fileDesc, &pagenum, &pagebuf)) == PFE_OK) {
        header = (SlottedPageHeader *)pagebuf;
        int freeSpace = header->freeSpacePtr - (sizeof(SlottedPageHeader) + header->numSlots * sizeof(Slot));
        if (freeSpace >= (length + sizeof(Slot))) {
            /* This page has enough space! */
            break;
        }
        PF_UnfixPage(fileDesc, pagenum, FALSE);
    }

    if (error == PFE_EOF) {
        /* 2. No page found, allocate a new one */
        if ((error = PF_AllocPage(fileDesc, &pagenum, &pagebuf)) != PFE_OK) {
            return error; /* Failed to allocate */
        }
        /* Initialize new page */
        header = (SlottedPageHeader *)pagebuf;
        header->numSlots = 0;
        header->freeSpacePtr = PF_PAGE_SIZE; /* Free space starts at the end */
    } else if (error != PFE_OK) {
        return error; /* Some other error */
    }

    /* 3. We now have a page (pagenum, pagebuf) with enough space. */
    header = (SlottedPageHeader *)pagebuf;

    /* Calculate new record offset */
    int newRecordOffset = header->freeSpacePtr - length;
    
    /* Add the record data */
    memcpy(pagebuf + newRecordOffset, record, length);
    
    /* Add the new slot */
    int newSlotNum = header->numSlots;
    newSlot = (Slot *)(pagebuf + sizeof(SlottedPageHeader) + (newSlotNum * sizeof(Slot)));
    newSlot->recordOffset = newRecordOffset;
    newSlot->recordLength = length;

    /* 4. Update header */
    header->numSlots++;
    header->freeSpacePtr = newRecordOffset;
    
    /* 5. Mark page dirty and unfix */
    if ((error = PF_UnfixPage(fileDesc, pagenum, TRUE)) != PFE_OK) {
        return error;
    }

    /* 6. Return the new RID */
    *newRid = MAKE_RID(pagenum, newSlotNum);
    return PFE_OK;
}

/* S_DeleteRecord would find the page, get the slot, and set length=0 */
/* S_GetRecord would find the page, get the slot, and return a pointer */