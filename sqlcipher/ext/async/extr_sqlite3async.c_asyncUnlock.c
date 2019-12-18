#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_7__ {TYPE_2__* pData; } ;
struct TYPE_5__ {int /*<<< orphan*/  eLock; } ;
struct TYPE_6__ {TYPE_1__ lock; scalar_t__ zName; } ;
typedef  TYPE_1__ AsyncFileLock ;
typedef  TYPE_2__ AsyncFileData ;
typedef  TYPE_3__ AsyncFile ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MUTEX_LOCK ; 
 int /*<<< orphan*/  ASYNC_MUTEX_QUEUE ; 
 int /*<<< orphan*/  ASYNC_UNLOCK ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 int SQLITE_OK ; 
 int addNewAsyncWrite (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asyncUnlock(sqlite3_file *pFile, int eLock){
  int rc = SQLITE_OK;
  AsyncFileData *p = ((AsyncFile *)pFile)->pData;
  if( p->zName ){
    AsyncFileLock *pLock = &p->lock;
    async_mutex_enter(ASYNC_MUTEX_QUEUE);
    async_mutex_enter(ASYNC_MUTEX_LOCK);
    pLock->eLock = MIN(pLock->eLock, eLock);
    rc = addNewAsyncWrite(p, ASYNC_UNLOCK, 0, eLock, 0);
    async_mutex_leave(ASYNC_MUTEX_LOCK);
    async_mutex_leave(ASYNC_MUTEX_QUEUE);
  }
  return rc;
}