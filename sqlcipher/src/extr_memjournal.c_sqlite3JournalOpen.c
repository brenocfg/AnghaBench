#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_io_methods ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_3__ {int nChunkSize; int nSpill; int flags; char const* zJournal; int /*<<< orphan*/ * pVfs; int /*<<< orphan*/  const* pMethod; } ;
typedef  TYPE_1__ MemJournal ;
typedef  int /*<<< orphan*/  FileChunk ;

/* Variables and functions */
 int MEMJOURNAL_DFLT_FILECHUNKSIZE ; 
 int /*<<< orphan*/  MemJournalMethods ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fileChunkSize (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3OsOpen (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int sqlite3JournalOpen(
  sqlite3_vfs *pVfs,         /* The VFS to use for actual file I/O */
  const char *zName,         /* Name of the journal file */
  sqlite3_file *pJfd,        /* Preallocated, blank file handle */
  int flags,                 /* Opening flags */
  int nSpill                 /* Bytes buffered before opening the file */
){
  MemJournal *p = (MemJournal*)pJfd;

  /* Zero the file-handle object. If nSpill was passed zero, initialize
  ** it using the sqlite3OsOpen() function of the underlying VFS. In this
  ** case none of the code in this module is executed as a result of calls
  ** made on the journal file-handle.  */
  memset(p, 0, sizeof(MemJournal));
  if( nSpill==0 ){
    return sqlite3OsOpen(pVfs, zName, pJfd, flags, 0);
  }

  if( nSpill>0 ){
    p->nChunkSize = nSpill;
  }else{
    p->nChunkSize = 8 + MEMJOURNAL_DFLT_FILECHUNKSIZE - sizeof(FileChunk);
    assert( MEMJOURNAL_DFLT_FILECHUNKSIZE==fileChunkSize(p->nChunkSize) );
  }

  p->pMethod = (const sqlite3_io_methods*)&MemJournalMethods;
  p->nSpill = nSpill;
  p->flags = flags;
  p->zJournal = zName;
  p->pVfs = pVfs;
  return SQLITE_OK;
}