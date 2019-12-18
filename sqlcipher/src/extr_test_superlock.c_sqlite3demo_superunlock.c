#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_9__ {int /*<<< orphan*/  db; scalar_t__ bWal; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* xShmLock ) (TYPE_2__*,int,int,int) ;} ;
typedef  TYPE_3__ Superlock ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_FILE_POINTER ; 
 int SQLITE_OK ; 
 int SQLITE_SHM_EXCLUSIVE ; 
 int SQLITE_SHM_NLOCK ; 
 int SQLITE_SHM_UNLOCK ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int sqlite3_file_control (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,int,int) ; 

void sqlite3demo_superunlock(void *pLock){
  Superlock *p = (Superlock *)pLock;
  if( p->bWal ){
    int rc;                         /* Return code */
    int flags = SQLITE_SHM_UNLOCK | SQLITE_SHM_EXCLUSIVE;
    sqlite3_file *fd = 0;
    rc = sqlite3_file_control(p->db, "main", SQLITE_FCNTL_FILE_POINTER, (void *)&fd);
    if( rc==SQLITE_OK ){
      fd->pMethods->xShmLock(fd, 2, 1, flags);
      fd->pMethods->xShmLock(fd, 3, SQLITE_SHM_NLOCK-3, flags);
    }
  }
  sqlite3_close(p->db);
  sqlite3_free(p);
}