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
struct TYPE_5__ {int (* xShmLock ) (TYPE_2__*,int,int,int) ;} ;
typedef  int /*<<< orphan*/  SuperlockBusy ;

/* Variables and functions */
 int SQLITE_BUSY ; 
 int SQLITE_SHM_EXCLUSIVE ; 
 int SQLITE_SHM_LOCK ; 
 scalar_t__ superlockBusyHandler (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int superlockShmLock(
  sqlite3_file *fd,               /* Database file handle */
  int idx,                        /* Offset of shm-lock to obtain */
  int nByte,                      /* Number of consective bytes to lock */
  SuperlockBusy *pBusy            /* Busy-handler wrapper object */
){
  int rc;
  int (*xShmLock)(sqlite3_file*, int, int, int) = fd->pMethods->xShmLock;
  do {
    rc = xShmLock(fd, idx, nByte, SQLITE_SHM_LOCK|SQLITE_SHM_EXCLUSIVE);
  }while( rc==SQLITE_BUSY && superlockBusyHandler((void *)pBusy, 0) );
  return rc;
}