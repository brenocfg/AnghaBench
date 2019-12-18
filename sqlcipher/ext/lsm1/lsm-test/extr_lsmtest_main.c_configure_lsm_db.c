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
 int /*<<< orphan*/ * tdb_lsm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdb_lsm_config_str (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static lsm_db *configure_lsm_db(TestDb *pDb){
  lsm_db *pLsm;
  pLsm = tdb_lsm(pDb);
  if( pLsm ){
    tdb_lsm_config_str(pDb, "mmap=1 autowork=1 automerge=4 worker_automerge=4");
  }
  return pLsm;
}