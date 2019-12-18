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
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_AUTOFLUSH ; 
 int /*<<< orphan*/  LSM_INFO_TREE_SIZE ; 
 int LSM_OK ; 
 int lsm_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int lsm_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mt_signal_worker (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int waitOnWorker(LsmDb *pDb){
  int rc;
  int nLimit = -1;
  int nSleep = 0;

  rc = lsm_config(pDb->db, LSM_CONFIG_AUTOFLUSH, &nLimit);
  do {
    int nOld, nNew, rc2;
    rc2 = lsm_info(pDb->db, LSM_INFO_TREE_SIZE, &nOld, &nNew);
    if( rc2!=LSM_OK ) return rc2;
    if( nOld==0 || nNew<(nLimit/2) ) break;
#ifdef LSM_MUTEX_PTHREADS
    mt_signal_worker(pDb, 0);
#endif
    usleep(5000);
    nSleep += 5;
  }while( 1 );

#if 0
  if( nSleep ) printf("# waitOnWorker(): nSleep=%d\n", nSleep);
#endif

  return rc;
}