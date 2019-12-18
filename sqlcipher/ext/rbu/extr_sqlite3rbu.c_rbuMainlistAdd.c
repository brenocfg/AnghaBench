#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_2__* pMainRbu; TYPE_2__* pMain; } ;
typedef  TYPE_1__ rbu_vfs ;
struct TYPE_5__ {int openFlags; scalar_t__ pRbu; struct TYPE_5__* pMainRbuNext; struct TYPE_5__* pMainNext; TYPE_1__* pRbuVfs; } ;
typedef  TYPE_2__ rbu_file ;

/* Variables and functions */
 int SQLITE_OPEN_MAIN_DB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuMainlistAdd(rbu_file *p){
  rbu_vfs *pRbuVfs = p->pRbuVfs;
  rbu_file *pIter;
  assert( (p->openFlags & SQLITE_OPEN_MAIN_DB) );
  sqlite3_mutex_enter(pRbuVfs->mutex);
  if( p->pRbu==0 ){
    for(pIter=pRbuVfs->pMain; pIter; pIter=pIter->pMainNext);
    p->pMainNext = pRbuVfs->pMain;
    pRbuVfs->pMain = p;
  }else{
    for(pIter=pRbuVfs->pMainRbu; pIter && pIter!=p; pIter=pIter->pMainRbuNext){}
    if( pIter==0 ){
      p->pMainRbuNext = pRbuVfs->pMainRbu;
      pRbuVfs->pMainRbu = p;
    }
  }
  sqlite3_mutex_leave(pRbuVfs->mutex);
}