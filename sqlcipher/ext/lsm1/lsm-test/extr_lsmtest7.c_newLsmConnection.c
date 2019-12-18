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

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_BLOCK_SIZE ; 
 int /*<<< orphan*/  LSM_CONFIG_PAGE_SIZE ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int lsm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tdb_lsm_env () ; 

__attribute__((used)) static lsm_db *newLsmConnection(
  const char *zDb, 
  int nPgsz, 
  int nBlksz,
  int *pRc
){
  lsm_db *db = 0;
  if( *pRc==0 ){
    int n1 = nPgsz;
    int n2 = nBlksz;
    *pRc = lsm_new(tdb_lsm_env(), &db);
    if( *pRc==0 ){
      if( n1 ) lsm_config(db, LSM_CONFIG_PAGE_SIZE, &n1);
      if( n2 ) lsm_config(db, LSM_CONFIG_BLOCK_SIZE, &n2);
      *pRc = lsm_open(db, "testdb.lsm");
    }
  }
  return db;
}