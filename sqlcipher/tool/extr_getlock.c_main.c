#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PENDING_BYTE ; 
 scalar_t__ RESERVED_BYTE ; 
 scalar_t__ SHARED_FIRST ; 
 int SHARED_SIZE ; 
 scalar_t__ SHM_CHECKPOINT ; 
 scalar_t__ SHM_READ_FIRST ; 
 int SHM_READ_SIZE ; 
 scalar_t__ SHM_RECOVER ; 
 scalar_t__ SHM_WRITE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isLocked (int,int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 char* malloc (int) ; 
 scalar_t__ memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv){
  int hDb;        /* File descriptor for the open database file */
  int hShm;       /* File descriptor for WAL shared-memory file */
  char *zShm;     /* Name of the shared-memory file for WAL mode */
  ssize_t got;    /* Bytes read from header */
  int isWal;                 /* True if in WAL mode */
  int nName;                 /* Length of filename */
  unsigned char aHdr[100];   /* Database header */
  int nLock = 0;             /* Number of locks held */
  int i;                     /* Loop counter */

  if( argc!=2 ) usage(argv[0]);
  hDb = open(argv[1], O_RDONLY, 0);
  if( hDb<0 ){
    fprintf(stderr, "cannot open %s\n", argv[1]);
    return 1;
  }

  /* Make sure we are dealing with an database file */
  got = read(hDb, aHdr, 100);
  if( got!=100 || memcmp(aHdr, "SQLite format 3",16)!=0 ){
    fprintf(stderr, "not an SQLite database: %s\n", argv[1]);
    exit(1);
  }

  /* First check for an exclusive lock */
  if( isLocked(hDb, F_RDLCK, SHARED_FIRST, SHARED_SIZE, "EXCLUSIVE") ){
    return 0;
  }
  isWal = aHdr[18]==2;
  if( isWal==0 ){
    /* Rollback mode */
    if( isLocked(hDb, F_RDLCK, PENDING_BYTE, 1, "PENDING") ) return 0;
    if( isLocked(hDb, F_RDLCK, RESERVED_BYTE, 1, "RESERVED") ) return 0;
    if( isLocked(hDb, F_WRLCK, SHARED_FIRST, SHARED_SIZE, "SHARED") ){
      return 0;
    }
  }else{
    /* WAL mode */
    nName = (int)strlen(argv[1]);
    zShm = malloc( nName + 100 );
    if( zShm==0 ){
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    memcpy(zShm, argv[1], nName);
    memcpy(&zShm[nName], "-shm", 5);
    hShm = open(zShm, O_RDONLY, 0);
    if( hShm<0 ){
      fprintf(stderr, "cannot open %s\n", zShm);
      return 1;
    }
    if( isLocked(hShm, F_RDLCK, SHM_RECOVER, 1, "WAL-RECOVERY") ){
      return 0;
    }
    nLock += isLocked(hShm, F_RDLCK, SHM_CHECKPOINT, 1, "WAL-CHECKPOINT");
    nLock += isLocked(hShm, F_RDLCK, SHM_WRITE, 1, "WAL-WRITE");
    for(i=0; i<SHM_READ_SIZE; i++){
      nLock += isLocked(hShm, F_WRLCK, SHM_READ_FIRST+i, 1, "WAL-READ");
    }
  }
  if( nLock==0 ){
    printf("file is not locked\n");
  }
  return 0;
}