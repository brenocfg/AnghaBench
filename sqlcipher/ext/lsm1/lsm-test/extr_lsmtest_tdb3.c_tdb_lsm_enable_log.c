#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  TestDb ;

/* Variables and functions */
 int /*<<< orphan*/  lsm_config_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * tdb_lsm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xLog ; 

void tdb_lsm_enable_log(TestDb *pDb, int bEnable){
  lsm_db *db = tdb_lsm(pDb);
  if( db ){
    lsm_config_log(db, (bEnable ? xLog : 0), (void *)"client");
  }
}