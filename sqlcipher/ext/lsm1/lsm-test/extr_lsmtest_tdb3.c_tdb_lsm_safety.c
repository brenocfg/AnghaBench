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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_SAFETY ; 
 int LSM_SAFETY_FULL ; 
 int LSM_SAFETY_NORMAL ; 
 int LSM_SAFETY_OFF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ tdb_lsm (int /*<<< orphan*/ *) ; 

void tdb_lsm_safety(TestDb *pDb, int eMode){
  assert( eMode==LSM_SAFETY_OFF 
       || eMode==LSM_SAFETY_NORMAL 
       || eMode==LSM_SAFETY_FULL 
  );
  if( tdb_lsm(pDb) ){
    int iParam = eMode;
    LsmDb *p = (LsmDb *)pDb;
    lsm_config(p->db, LSM_CONFIG_SAFETY, &iParam);
  }
}