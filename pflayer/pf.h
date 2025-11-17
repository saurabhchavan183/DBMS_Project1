// /* pf.h: externs and error codes for Paged File Interface*/
// #ifndef TRUE
// #define TRUE 1		
// #endif
// #ifndef FALSE
// #define FALSE 0
// #endif

// /* NEW: Definition for Page Replacement Strategy */
// typedef enum {
//     PF_LRU,
//     PF_MRU
// } PF_Strategy;

// /************** Error Codes *********************************/
// #define PFE_OK		0	/* OK */
// #define PFE_NOMEM	-1	/* no memory */
// #define PFE_NOBUF	-2	/* no buffer space */
// #define PFE_PAGEFIXED 	-3	/* page already fixed in buffer */
// #define PFE_PAGENOTINBUF -4	/* page to be unfixed is not in the buffer */
// #define PFE_UNIX	-5	/* unix error */
// #define PFE_INCOMPLETEREAD -6	/* incomplete read of page from file */
// #define PFE_INCOMPLETEWRITE -7	/* incomplete write of page to file */
// #define PFE_HDRREAD	-8	/* incomplete read of header from file */
// #define PFE_HDRWRITE	-9	/* incomplte write of header to file */
// #define PFE_INVALIDPAGE -10	/* invalid page number */
// #define PFE_FILEOPEN	-11	/* file already open */
// #define	PFE_FTABFULL	-12	/* file table is full */
// #define PFE_FD		-13	/* invalid file descriptor */
// #define PFE_EOF		-14	/* end of file */
// #define PFE_PAGEFREE	-15	/* page already free */
// #define PFE_PAGEUNFIXED	-16	/* page already unfixed */

// /* Internal error: please report to the TA */
// #define PFE_PAGEINBUF	-17	/* new page to be allocated already in buffer */
// #define PFE_HASHNOTFOUND -18	/* hash table entry not found */
// #define PFE_HASHPAGEEXIST -19	/* page already exist in hash table */


// /* page size */
// #define PF_PAGE_SIZE	4096

// /* externs from the PF layer */
// extern int PFerrno;		/* error number of last error */
// // extern void PF_Init();
// extern void PF_Init(int num_bufs, PF_Strategy strategy); /* MODIFIED */
// extern void PF_PrintError();

// /* NEW: Stats function prototypes */
// extern void PF_ResetStats();
// extern void PF_GetStats(int *log_reads, int *log_writes, int *phys_reads, int *phys_writes, int *pages_acc);

/* pf.h: externs and error codes for Paged File Interface*/
#ifndef TRUE
#define TRUE 1		
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* Definition for Page Replacement Strategy */
typedef enum {
    PF_LRU,
    PF_MRU
} PF_Strategy;

/************** Error Codes *********************************/
#define PFE_OK		0	/* OK */
#define PFE_NOMEM	-1	/* no memory */
#define PFE_NOBUF	-2	/* no buffer space */
#define PFE_PAGEFIXED 	-3	/* page already fixed in buffer */
#define PFE_PAGENOTINBUF -4	/* page to be unfixed is not in the buffer */
#define PFE_UNIX	-5	/* unix error */
#define PFE_INCOMPLETEREAD -6	/* incomplete read of page from file */
#define PFE_INCOMPLETEWRITE -7	/* incomplete write of page to file */
#define PFE_HDRREAD	-8	/* incomplete read of header from file */
#define PFE_HDRWRITE	-9	/* incomplte write of header to file */
#define PFE_INVALIDPAGE -10	/* invalid page number */
#define PFE_FILEOPEN	-11	/* file already open */
#define	PFE_FTABFULL	-12	/* file table is full */
#define PFE_FD		-13	/* invalid file descriptor */
#define PFE_EOF		-14	/* end of file */
#define PFE_PAGEFREE	-15	/* page already free */
#define PFE_PAGEUNFIXED	-16	/* page already unfixed */
#define PFE_PAGEINBUF	-17	/* new page to be allocated already in buffer */
#define PFE_HASHNOTFOUND -18	/* hash table entry not found */
#define PFE_HASHPAGEEXIST -19	/* page already exist in hash table */


/* page size */
#define PF_PAGE_SIZE	4096

/* externs from the PF layer */
extern int PFerrno;		/* error number of last error */

/* PF layer function prototypes */
extern void PF_Init(int num_bufs, PF_Strategy strategy);
extern void PF_PrintError(char *s);
extern int PF_CreateFile(char *fname);
extern int PF_DestroyFile(char *fname);
extern int PF_OpenFile(char *fname);
extern int PF_CloseFile(int fd);
extern int PF_GetFirstPage(int fd, int *pagenum, char **pagebuf);
extern int PF_GetNextPage(int fd, int *pagenum, char **pagebuf);
extern int PF_GetThisPage(int fd, int pagenum, char **pagebuf);
extern int PF_AllocPage(int fd, int *pagenum, char **pagebuf);
extern int PF_DisposePage(int fd, int pagenum);
extern int PF_UnfixPage(int fd, int pagenum, int dirty);

/* Statistics function prototypes */
extern void PF_ResetStats();
extern void PF_GetStats(int *log_reads, int *log_writes, int *phys_reads, int *phys_writes, int *pages_acc);

/* NOTE: The extra '}' at the end has been removed */
/* NEW: Add this prototype */
extern void PFbufPrint();