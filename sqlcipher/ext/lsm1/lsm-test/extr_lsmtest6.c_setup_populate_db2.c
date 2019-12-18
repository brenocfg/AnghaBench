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
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  LSMTEST6_TESTDB ; 
 int /*<<< orphan*/  LSM_CONFIG_AUTOFLUSH ; 
 int /*<<< orphan*/  LSM_CONFIG_BLOCK_SIZE ; 
 int /*<<< orphan*/  LSM_CONFIG_PAGE_SIZE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * getDatasource () ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lsm_insert (int /*<<< orphan*/ *,void*,int,void*,int) ; 
 int lsm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdb_lsm_env () ; 
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,void**,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDeleteLsmdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testSaveDb (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void setup_populate_db2(void){
  Datasource *pData;
  int ii;
  int rc;
  int nBlocksize = 64*1024;
  int nPagesize = 1024;
  int nWritebuffer = 4*1024;
  lsm_db *pDb;

  testDeleteLsmdb(LSMTEST6_TESTDB);
  rc = lsm_new(tdb_lsm_env(), &pDb);
  if( rc==LSM_OK ) rc = lsm_open(pDb, LSMTEST6_TESTDB);

  lsm_config(pDb, LSM_CONFIG_BLOCK_SIZE, &nBlocksize); 
  lsm_config(pDb, LSM_CONFIG_PAGE_SIZE, &nPagesize); 
  lsm_config(pDb, LSM_CONFIG_AUTOFLUSH, &nWritebuffer); 

  pData = getDatasource();
  for(ii=0; rc==LSM_OK && ii<5000; ii++){
    void *pKey; int nKey;
    void *pVal; int nVal;
    testDatasourceEntry(pData, ii, &pKey, &nKey, &pVal, &nVal);
    lsm_insert(pDb, pKey, nKey, pVal, nVal);
  }
  testDatasourceFree(pData);
  lsm_close(pDb);

  testSaveDb(LSMTEST6_TESTDB, "log");
  assert( rc==LSM_OK );
}