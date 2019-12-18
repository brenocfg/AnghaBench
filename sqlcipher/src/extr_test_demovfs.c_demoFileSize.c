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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DemoFile ;

/* Variables and functions */
 int SQLITE_IOERR_FSTAT ; 
 int SQLITE_OK ; 
 int demoFlushBuffer (TYPE_1__*) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int demoFileSize(sqlite3_file *pFile, sqlite_int64 *pSize){
  DemoFile *p = (DemoFile*)pFile;
  int rc;                         /* Return code from fstat() call */
  struct stat sStat;              /* Output of fstat() call */

  /* Flush the contents of the buffer to disk. As with the flush in the
  ** demoRead() method, it would be possible to avoid this and save a write
  ** here and there. But in practice this comes up so infrequently it is
  ** not worth the trouble.
  */
  rc = demoFlushBuffer(p);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  rc = fstat(p->fd, &sStat);
  if( rc!=0 ) return SQLITE_IOERR_FSTAT;
  *pSize = sStat.st_size;
  return SQLITE_OK;
}