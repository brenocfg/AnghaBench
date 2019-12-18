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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DemoFile ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int SQLITE_IOERR_READ ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int demoFlushBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int demoRead(
  sqlite3_file *pFile, 
  void *zBuf, 
  int iAmt, 
  sqlite_int64 iOfst
){
  DemoFile *p = (DemoFile*)pFile;
  off_t ofst;                     /* Return value from lseek() */
  int nRead;                      /* Return value from read() */
  int rc;                         /* Return code from demoFlushBuffer() */

  /* Flush any data in the write buffer to disk in case this operation
  ** is trying to read data the file-region currently cached in the buffer.
  ** It would be possible to detect this case and possibly save an 
  ** unnecessary write here, but in practice SQLite will rarely read from
  ** a journal file when there is data cached in the write-buffer.
  */
  rc = demoFlushBuffer(p);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  ofst = lseek(p->fd, iOfst, SEEK_SET);
  if( ofst!=iOfst ){
    return SQLITE_IOERR_READ;
  }
  nRead = read(p->fd, zBuf, iAmt);

  if( nRead==iAmt ){
    return SQLITE_OK;
  }else if( nRead>=0 ){
    return SQLITE_IOERR_SHORT_READ;
  }

  return SQLITE_IOERR_READ;
}