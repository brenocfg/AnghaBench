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
typedef  int /*<<< orphan*/  OomTest ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  LSMTEST6_TESTDB ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * getDatasource () ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDeleteLsmdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testOomAssertRc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testOomEnable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testOomFetchData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testOomOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testOomWriteData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void simple_oom2_1(OomTest *pOom){
  const int nRecord = 100;        /* Number of records initially in db */
  const int nIns = 10;            /* Number of records inserted with OOM */

  Datasource *pData = getDatasource();
  int rc = LSM_OK;
  lsm_db *pDb1;
  lsm_db *pDb2;
  int i;

  testDeleteLsmdb(LSMTEST6_TESTDB);

  /* Open the two connections. Initialize the in-memory tree so that it
  ** contains 100 records. Do all this with OOM injection disabled. */
  testOomEnable(pOom, 0);
  testOomOpen(pOom, LSMTEST6_TESTDB, &pDb1, &rc);
  testOomOpen(pOom, LSMTEST6_TESTDB, &pDb2, &rc);
  for(i=0; i<nRecord; i++){
    testOomWriteData(pOom, pDb1, pData, i, &rc);
  }
  testOomEnable(pOom, 1);
  assert( rc==0 );

  /* Insert 10 more records using pDb1. Stop when an OOM is encountered. */
  for(i=nRecord; i<nRecord+nIns; i++){
    testOomWriteData(pOom, pDb1, pData, i, &rc);
    if( rc ) break;
  }
  testOomAssertRc(pOom, rc);

  /* Switch off OOM injection. Write a few rows using pDb2. Then check
  ** that the database may be successfully queried.  */
  testOomEnable(pOom, 0);
  rc = 0;
  for(; i<nRecord+nIns && rc==0; i++){
    testOomWriteData(pOom, pDb2, pData, i, &rc);
  }
  for(i=0; i<nRecord+nIns; i++) testOomFetchData(pOom, pDb2, pData, i, &rc);
  testOomEnable(pOom, 1);

  lsm_close(pDb1);
  lsm_close(pDb2);
  testDatasourceFree(pData);
}