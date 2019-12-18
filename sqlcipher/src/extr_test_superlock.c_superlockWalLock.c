#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int (* xShmMap ) (TYPE_2__*,int /*<<< orphan*/ ,int,int,void volatile**) ;} ;
typedef  int /*<<< orphan*/  SuperlockBusy ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_FILE_POINTER ; 
 int SQLITE_OK ; 
 int SQLITE_SHM_NLOCK ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int sqlite3_file_control (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int,void volatile**) ; 
 int superlockShmLock (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int superlockWalLock(
  sqlite3 *db,                    /* Database handle open on WAL database */
  SuperlockBusy *pBusy            /* Busy handler wrapper object */
){
  int rc;                         /* Return code */
  sqlite3_file *fd = 0;           /* Main database file handle */
  void volatile *p = 0;           /* Pointer to first page of shared memory */

  /* Obtain a pointer to the sqlite3_file object open on the main db file. */
  rc = sqlite3_file_control(db, "main", SQLITE_FCNTL_FILE_POINTER, (void *)&fd);
  if( rc!=SQLITE_OK ) return rc;

  /* Obtain the "recovery" lock. Normally, this lock is only obtained by
  ** clients running database recovery.  
  */
  rc = superlockShmLock(fd, 2, 1, pBusy);
  if( rc!=SQLITE_OK ) return rc;

  /* Zero the start of the first shared-memory page. This means that any
  ** clients that open read or write transactions from this point on will
  ** have to run recovery before proceeding. Since they need the "recovery"
  ** lock that this process is holding to do that, no new read or write
  ** transactions may now be opened. Nor can a checkpoint be run, for the
  ** same reason.
  */
  rc = fd->pMethods->xShmMap(fd, 0, 32*1024, 1, &p);
  if( rc!=SQLITE_OK ) return rc;
  memset((void *)p, 0, 32);

  /* Obtain exclusive locks on all the "read-lock" slots. Once these locks
  ** are held, it is guaranteed that there are no active reader, writer or 
  ** checkpointer clients.
  */
  rc = superlockShmLock(fd, 3, SQLITE_SHM_NLOCK-3, pBusy);
  return rc;
}