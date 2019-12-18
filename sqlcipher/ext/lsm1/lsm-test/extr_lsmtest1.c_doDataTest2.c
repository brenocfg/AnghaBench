#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_3__ {int nIter; int nWrite; int nRange; int /*<<< orphan*/  defn; } ;
typedef  TYPE_1__ Datatest2 ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_AUTOFLUSH ; 
 int LSM_OK ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  lsm_config (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ tdb_lsm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCaseFinish (int) ; 
 int /*<<< orphan*/  testCaseNDot () ; 
 int /*<<< orphan*/  testCaseProgress (int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCompareDb (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int testControlDb (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDeleteRange (int /*<<< orphan*/ *,void*,int,void*,int,int*) ; 
 int /*<<< orphan*/  testFree (void*) ; 
 void* testMallocCopy (void*,int) ; 
 int /*<<< orphan*/ * testOpen (char const*,int,int*) ; 
 int /*<<< orphan*/  testReopen (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testReopenRecover (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testWriteDatasource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void doDataTest2(
  const char *zSystem,            /* Database system to test */
  int bRecover,
  Datatest2 *p,                   /* Structure containing test parameters */
  int *pRc                        /* OUT: Error code */
){
  TestDb *pDb;
  TestDb *pControl;
  Datasource *pData;
  int i;
  int rc = LSM_OK;
  int iDot = 0;

  /* Start the test case, open a database and allocate the datasource. */
  pDb = testOpen(zSystem, 1, &rc);
  pData = testDatasourceNew(&p->defn);
  rc = testControlDb(&pControl);

  if( tdb_lsm(pDb) ){
    int nBuf = 32 * 1024 * 1024;
    lsm_config(tdb_lsm(pDb), LSM_CONFIG_AUTOFLUSH, &nBuf);
  }

  for(i=0; rc==0 && i<p->nIter; i++){
    void *pKey1; int nKey1;
    void *pKey2; int nKey2;
    int ii;
    int nRange = MIN(p->nIter*p->nWrite, p->nRange);

    for(ii=0; rc==0 && ii<p->nWrite; ii++){
      int iKey = (i*p->nWrite + ii) % p->nRange;
      testWriteDatasource(pControl, pData, iKey, &rc);
      testWriteDatasource(pDb, pData, iKey, &rc);
    }

    testDatasourceEntry(pData, i+1000000, &pKey1, &nKey1, 0, 0);
    pKey1 = testMallocCopy(pKey1, nKey1);
    testDatasourceEntry(pData, i+2000000, &pKey2, &nKey2, 0, 0);

    testDeleteRange(pDb, pKey1, nKey1, pKey2, nKey2, &rc);
    testDeleteRange(pControl, pKey1, nKey1, pKey2, nKey2, &rc);
    testFree(pKey1);

    testCompareDb(pData, nRange, i, pControl, pDb, &rc);
    if( bRecover ){
      testReopenRecover(&pDb, &rc);
    }else{
      testReopen(&pDb, &rc);
    }
    testCompareDb(pData, nRange, i, pControl, pDb, &rc);

    /* Update the progress dots... */
    testCaseProgress(i, p->nIter, testCaseNDot(), &iDot);
  }

  testClose(&pDb);
  testClose(&pControl);
  testDatasourceFree(pData);
  testCaseFinish(rc);
  *pRc = rc;
}