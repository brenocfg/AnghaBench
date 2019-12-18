#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_4__ {scalar_t__ nBuffer; scalar_t__ iBufferOfst; int /*<<< orphan*/ * aBuffer; } ;
typedef  TYPE_1__ DemoFile ;

/* Variables and functions */
 scalar_t__ SQLITE_DEMOVFS_BUFFERSZ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int demoDirectWrite (TYPE_1__*,void const*,int,scalar_t__) ; 
 int demoFlushBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int demoWrite(
  sqlite3_file *pFile, 
  const void *zBuf, 
  int iAmt, 
  sqlite_int64 iOfst
){
  DemoFile *p = (DemoFile*)pFile;
  
  if( p->aBuffer ){
    char *z = (char *)zBuf;       /* Pointer to remaining data to write */
    int n = iAmt;                 /* Number of bytes at z */
    sqlite3_int64 i = iOfst;      /* File offset to write to */

    while( n>0 ){
      int nCopy;                  /* Number of bytes to copy into buffer */

      /* If the buffer is full, or if this data is not being written directly
      ** following the data already buffered, flush the buffer. Flushing
      ** the buffer is a no-op if it is empty.  
      */
      if( p->nBuffer==SQLITE_DEMOVFS_BUFFERSZ || p->iBufferOfst+p->nBuffer!=i ){
        int rc = demoFlushBuffer(p);
        if( rc!=SQLITE_OK ){
          return rc;
        }
      }
      assert( p->nBuffer==0 || p->iBufferOfst+p->nBuffer==i );
      p->iBufferOfst = i - p->nBuffer;

      /* Copy as much data as possible into the buffer. */
      nCopy = SQLITE_DEMOVFS_BUFFERSZ - p->nBuffer;
      if( nCopy>n ){
        nCopy = n;
      }
      memcpy(&p->aBuffer[p->nBuffer], z, nCopy);
      p->nBuffer += nCopy;

      n -= nCopy;
      i += nCopy;
      z += nCopy;
    }
  }else{
    return demoDirectWrite(p, zBuf, iAmt, iOfst);
  }

  return SQLITE_OK;
}