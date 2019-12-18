#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nLogsize; int bDoWork; int /*<<< orphan*/  ckpter_mutex; int /*<<< orphan*/  ckpter_cond; } ;
typedef  TYPE_1__ bt_ckpter ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bgc_logsize_cb(void *pCtx, int nLogsize){
  bt_ckpter *p = (bt_ckpter*)pCtx;
  if( nLogsize>=p->nLogsize ){
    pthread_mutex_lock(&p->ckpter_mutex);
    p->bDoWork = 1;
    pthread_cond_signal(&p->ckpter_cond);
    pthread_mutex_unlock(&p->ckpter_mutex);
  }
}