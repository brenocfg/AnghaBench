#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_6__ {TYPE_2__* pData; } ;
struct TYPE_4__ {int eLock; } ;
struct TYPE_5__ {TYPE_1__ lock; } ;
typedef  TYPE_3__ AsyncFile ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MUTEX_LOCK ; 
#define  SQLITE_FCNTL_LOCKSTATE 128 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  async_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asyncFileControl(sqlite3_file *id, int op, void *pArg){
  switch( op ){
    case SQLITE_FCNTL_LOCKSTATE: {
      async_mutex_enter(ASYNC_MUTEX_LOCK);
      *(int*)pArg = ((AsyncFile*)id)->pData->lock.eLock;
      async_mutex_leave(ASYNC_MUTEX_LOCK);
      return SQLITE_OK;
    }
  }
  return SQLITE_NOTFOUND;
}