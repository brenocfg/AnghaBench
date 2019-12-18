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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_5__ {int nWorker; TYPE_1__* aWorker; int /*<<< orphan*/  db; } ;
struct TYPE_4__ {int /*<<< orphan*/  pWorker; } ;
typedef  TYPE_2__ LsmDb ;

/* Variables and functions */
 scalar_t__ tdb_lsm (int /*<<< orphan*/ *) ; 
 int test_lsm_config_str (TYPE_2__*,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 

int tdb_lsm_config_str(TestDb *pDb, const char *zStr){
  int rc = 0;
  if( tdb_lsm(pDb) ){
#ifdef LSM_MUTEX_PTHREADS
    int i;
#endif
    LsmDb *pLsm = (LsmDb *)pDb;

    rc = test_lsm_config_str(pLsm, pLsm->db, 0, zStr, 0);
#ifdef LSM_MUTEX_PTHREADS
    for(i=0; rc==0 && i<pLsm->nWorker; i++){
      rc = test_lsm_config_str(0, pLsm->aWorker[i].pWorker, 1, zStr, 0);
    }
#endif
  }
  return rc;
}