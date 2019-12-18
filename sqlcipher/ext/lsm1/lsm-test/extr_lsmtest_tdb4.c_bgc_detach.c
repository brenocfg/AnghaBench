#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nRef; int bDoWork; int /*<<< orphan*/  spec; int /*<<< orphan*/  file; int /*<<< orphan*/  ckpter_mutex; int /*<<< orphan*/  ckpter_cond; int /*<<< orphan*/  ckpter_thread; struct TYPE_6__* pNext; } ;
typedef  TYPE_1__ bt_ckpter ;
struct TYPE_8__ {TYPE_1__* pCkpter; } ;
struct TYPE_7__ {TYPE_1__* pCkpter; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ BtDb ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE4_MUTEX_STATIC_KV ; 
 int SQLITE4_OK ; 
 TYPE_4__ gBgc ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite4_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite4_mutex_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite4_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite4_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testFree (TYPE_1__*) ; 

__attribute__((used)) static int bgc_detach(BtDb *pDb){
  int rc = SQLITE4_OK;
  bt_ckpter *pCkpter = pDb->pCkpter;
  if( pCkpter ){
    int bShutdown = 0;            /* True if this is the last reference */

    sqlite4_mutex_enter(sqlite4_mutex_alloc(pDb->pEnv,SQLITE4_MUTEX_STATIC_KV));
    pCkpter->nRef--;
    if( pCkpter->nRef==0 ){
      bt_ckpter **pp;

      *pp = pCkpter->pNext;
      for(pp=&gBgc.pCkpter; *pp!=pCkpter; pp=&((*pp)->pNext));
      bShutdown = 1;
    }
    sqlite4_mutex_leave(sqlite4_mutex_alloc(pDb->pEnv,SQLITE4_MUTEX_STATIC_KV));

    if( bShutdown ){
      void *pDummy;

      /* Signal the checkpointer thread. */
      pthread_mutex_lock(&pCkpter->ckpter_mutex);
      pCkpter->bDoWork = 1;
      pthread_cond_signal(&pCkpter->ckpter_cond);
      pthread_mutex_unlock(&pCkpter->ckpter_mutex);

      /* Join the checkpointer thread. */
      pthread_join(pCkpter->ckpter_thread, &pDummy);
      pthread_cond_destroy(&pCkpter->ckpter_cond);
      pthread_mutex_destroy(&pCkpter->ckpter_mutex);

      sqlite4_buffer_clear(&pCkpter->file);
      sqlite4_buffer_clear(&pCkpter->spec);
      testFree(pCkpter);
    }

    pDb->pCkpter = 0;
  }
  return rc;
}