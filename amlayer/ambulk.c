/* amlayer/ambulk.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "am.h"
#include "pf.h"

/* (Helper struct for sorting) */
typedef struct {
    char key[AM_MAXATTRLENGTH];
    int recId;
} KeyRecPair;

/* (Comparison function for qsort) */
int compare_pairs(const void *a, const void *b) {
    /* (This needs to be implemented based on attrType) */
    /* ... */
}

/* * This is a highly simplified sketch. A real implementation 
 * needs to handle recursion, page management, and parent
 * node creation properly.
 */

int AM_BulkLoad(int fileDesc, char *dataFileName, char attrType, int attrLength) {
    /* 1. Read all (key, recId) pairs from dataFileName into memory. */
    /* ... (code to read file, parse, store in a large KeyRecPair array) ... */
    int num_records; /* = number of records read */
    KeyRecPair *records; /* = array of records */

    /* 2. Sort the pairs in memory */
    /* qsort(records, num_records, sizeof(KeyRecPair), compare_pairs); */

    /* 3. Build the leaf layer */
    int *leaf_page_nums = malloc(num_records * sizeof(int));
    char **promoted_keys = malloc(num_records * sizeof(char*));
    int num_leaf_pages = 0;
    
    int current_record = 0;
    while (current_record < num_records) {
        char *leafPageBuf;
        int leafPageNum;
        PF_AllocPage(fileDesc, &leafPageNum, &leafPageBuf);
        AM_LEAFHEADER *leaf_header = (AM_LEAFHEADER *)leafPageBuf;
        /* (Initialize leaf_header: pageType='l', numKeys=0, etc.) */

        /* Store the first key for parent promotion */
        promoted_keys[num_leaf_pages] = malloc(attrLength);
        memcpy(promoted_keys[num_leaf_pages], records[current_record].key, attrLength);
        leaf_page_nums[num_leaf_pages] = leafPageNum;
        num_leaf_pages++;

        /* 4. Pack the leaf page */
        while (current_record < num_records) {
            /* (Use AM_InsertintoLeaf logic to add key/recId to leafPageBuf) */
            /* (This is simplified; AM_InsertintoLeaf is complex) */
            /* (A better way is to just write them sequentially) */
            
            /* (Check if page is full) */
            /* if (leaf_header->keyPtr > (PF_PAGE_SIZE - ...)) {
                   break; // Page is full
               } */
            
            /* (Add record...) */
            
            current_record++;
        }
        
        /* (Link to next leaf: leaf_header->nextLeafPage = ...) */
        PF_UnfixPage(fileDesc, leafPageNum, TRUE);
    }
    
    /* 5. Recursively build internal nodes */
    /* You now have a list of (promoted_keys[i], leaf_page_nums[i]).
       You must now build a B+ tree on *these* pairs.
       This is a recursive process:
       - Pack (key, pageNum) pairs into new internal nodes.
       - When an internal node is full, promote *its* first key
         to the *next* level up.
       - Repeat until only one root node remains.
    */
    
    /* int newRootPageNum = build_internal_layers_recursive(fileDesc, 
                                promoted_keys, leaf_page_nums, num_leaf_pages, 
                                attrType, attrLength); */
                                
    /* 6. Update the global Root Page Number */
    /* AM_RootPageNum = newRootPageNum; */
    
    /* (Free all temporary memory) */
    
    return AME_OK;
}