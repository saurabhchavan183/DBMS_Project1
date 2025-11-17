/* slotted/slotted.h */
#ifndef _SLOTTED_H
#define _SLOTTED_H

#include "pf.h"

/* * A Record ID (RID) is composed of a page number and a slot number.
 * We can pack this into a single int.
 * 16 bits for page number (max 65,536 pages)
 * 16 bits for slot number (max 65,536 slots per page)
 */
typedef int RID;
#define MAKE_RID(pageNum, slotNum) ((((pageNum) & 0xFFFF) << 16) | ((slotNum) & 0xFFFF))
#define GET_PAGE_NUM(rid) (((rid) >> 16) & 0xFFFF)
#define GET_SLOT_NUM(rid) ((rid) & 0xFFFF)

/*
 * Slotted Page Structure:
 * -----------------------------------------------------------------
 * | Page Header | ... Free Space ... | Slot 1 | Slot 2 | ... | Slot N |
 * -----------------------------------------------------------------
 * ^             ^                    ^
 * |             |                    |
 * Page Start    End of Slots         Free Space Ptr
 * (Slot 0)      (header.freePtr)     (grows left)
 * (grows right)
 *
 * Slots store (offset, length) pairs.
 * Records are stored from the end of the page, growing left.
 */

typedef struct {
    int recordOffset;
    int recordLength;
} Slot;

typedef struct {
    int numSlots;       /* Number of slots in use on this page */
    int freeSpacePtr;   /* Offset to the start of free space */
    /* Add more metadata if needed, e.g., page's free space */
} SlottedPageHeader;

/* API Functions */
int S_CreateFile(char *filename);
int S_DestroyFile(char *filename);
int S_OpenFile(char *filename);
int S_CloseFile(int fileDesc);

int S_InsertRecord(int fileDesc, char *record, int length, RID *newRid);
int S_DeleteRecord(int fileDesc, RID rid);
int S_GetRecord(int fileDesc, RID rid, char **record, int *length);

/* (You would also add sequential scan functions) */

#endif /* _SLOTTED_H */