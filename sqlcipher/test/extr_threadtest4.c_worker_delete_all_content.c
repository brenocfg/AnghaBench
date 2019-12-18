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
struct TYPE_4__ {int /*<<< orphan*/  nTest; int /*<<< orphan*/  pWrMutex; int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ WorkerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_sql (TYPE_1__*,char*,...) ; 

__attribute__((used)) static void worker_delete_all_content(WorkerInfo *p, int inTrans){
  if( inTrans ){
    pthread_mutex_lock(p->pWrMutex);
    run_sql(p, "BEGIN");
    run_sql(p, "DELETE FROM t1 WHERE tid=%d", p->tid);
    run_sql(p, "DELETE FROM t2 WHERE tid=%d", p->tid);
    run_sql(p, "DELETE FROM t3 WHERE tid=%d", p->tid);
    run_sql(p, "COMMIT");
    pthread_mutex_unlock(p->pWrMutex);
    p->nTest++;
  }else{
    pthread_mutex_lock(p->pWrMutex);
    run_sql(p, "DELETE FROM t1 WHERE tid=%d", p->tid);
    pthread_mutex_unlock(p->pWrMutex);
    p->nTest++;
    pthread_mutex_lock(p->pWrMutex);
    run_sql(p, "DELETE FROM t2 WHERE tid=%d", p->tid);
    pthread_mutex_unlock(p->pWrMutex);
    p->nTest++;
    pthread_mutex_lock(p->pWrMutex);
    run_sql(p, "DELETE FROM t3 WHERE tid=%d", p->tid);
    pthread_mutex_unlock(p->pWrMutex);
    p->nTest++;
  }
}