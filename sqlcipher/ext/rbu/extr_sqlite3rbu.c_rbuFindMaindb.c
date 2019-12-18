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
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_2__* pMain; TYPE_2__* pMainRbu; } ;
typedef  TYPE_1__ rbu_vfs ;
struct TYPE_6__ {char const* zWal; struct TYPE_6__* pMainNext; struct TYPE_6__* pMainRbuNext; } ;
typedef  TYPE_2__ rbu_file ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rbu_file *rbuFindMaindb(rbu_vfs *pRbuVfs, const char *zWal, int bRbu){
  rbu_file *pDb;
  sqlite3_mutex_enter(pRbuVfs->mutex);
  if( bRbu ){
    for(pDb=pRbuVfs->pMainRbu; pDb && pDb->zWal!=zWal; pDb=pDb->pMainRbuNext){}
  }else{
    for(pDb=pRbuVfs->pMain; pDb && pDb->zWal!=zWal; pDb=pDb->pMainNext){}
  }
  sqlite3_mutex_leave(pRbuVfs->mutex);
  return pDb;
}