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
struct TYPE_4__ {int (* xProgress ) (void*) ;unsigned int nProgressOps; int /*<<< orphan*/  mutex; void* pProgressArg; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

void sqlite3_progress_handler(
  sqlite3 *db, 
  int nOps,
  int (*xProgress)(void*), 
  void *pArg
){
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) ){
    (void)SQLITE_MISUSE_BKPT;
    return;
  }
#endif
  sqlite3_mutex_enter(db->mutex);
  if( nOps>0 ){
    db->xProgress = xProgress;
    db->nProgressOps = (unsigned)nOps;
    db->pProgressArg = pArg;
  }else{
    db->xProgress = 0;
    db->nProgressOps = 0;
    db->pProgressArg = 0;
  }
  sqlite3_mutex_leave(db->mutex);
}