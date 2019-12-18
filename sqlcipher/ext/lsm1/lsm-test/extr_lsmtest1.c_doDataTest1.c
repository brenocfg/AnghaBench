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
struct TYPE_3__ {int nRow; int nVerify; int /*<<< orphan*/  bTestScan; int /*<<< orphan*/  nTest; int /*<<< orphan*/  defn; } ;
typedef  TYPE_1__ Datatest1 ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testBegin (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testCaseFinish (int) ; 
 int testCaseNDot () ; 
 int /*<<< orphan*/  testCaseProgress (int,int,int,int*) ; 
 int /*<<< orphan*/  testCommit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDbContents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testDeleteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/ * testOpen (char const*,int,int*) ; 
 int /*<<< orphan*/  testReopen (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testReopenRecover (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 

__attribute__((used)) static void doDataTest1(
  const char *zSystem,            /* Database system to test */
  int bRecover,
  Datatest1 *p,                   /* Structure containing test parameters */
  int *pRc                        /* OUT: Error code */
){
  int i;
  int iDot;
  int rc = LSM_OK;
  Datasource *pData;
  TestDb *pDb;
  int iToggle = 0;

  /* Start the test case, open a database and allocate the datasource. */
  pDb = testOpen(zSystem, 1, &rc);
  pData = testDatasourceNew(&p->defn);

  i = 0;
  iDot = 0;
  while( rc==LSM_OK && i<p->nRow ){

    /* Insert some data */
    testWriteDatasourceRange(pDb, pData, i, p->nVerify, &rc);
    i += p->nVerify;

    if( iToggle ) testBegin(pDb, 1, &rc);
    /* Check that the db content is correct. */
    testDbContents(pDb, pData, p->nRow, 0, i-1, p->nTest, p->bTestScan, &rc);
    if( iToggle ) testCommit(pDb, 0, &rc);
    iToggle = (iToggle+1)%2;

    if( bRecover ){
      testReopenRecover(&pDb, &rc);
    }else{
      testReopen(&pDb, &rc);
    }

    /* Check that the db content is still correct. */
    testDbContents(pDb, pData, p->nRow, 0, i-1, p->nTest, p->bTestScan, &rc);

    /* Update the progress dots... */
    testCaseProgress(i, p->nRow, testCaseNDot()/2, &iDot);
  }

  i = 0;
  iDot = 0;
  while( rc==LSM_OK && i<p->nRow ){

    /* Delete some entries */
    testDeleteDatasourceRange(pDb, pData, i, p->nVerify, &rc);
    i += p->nVerify;

    /* Check that the db content is correct. */
    testDbContents(pDb, pData, p->nRow, i, p->nRow-1,p->nTest,p->bTestScan,&rc);

    /* Close and reopen the database. */
    if( bRecover ){
      testReopenRecover(&pDb, &rc);
    }else{
      testReopen(&pDb, &rc);
    }

    /* Check that the db content is still correct. */
    testDbContents(pDb, pData, p->nRow, i, p->nRow-1,p->nTest,p->bTestScan,&rc);

    /* Update the progress dots... */
    testCaseProgress(i, p->nRow, testCaseNDot()/2, &iDot);
  }

  /* Free the datasource, close the database and finish the test case. */
  testDatasourceFree(pData);
  tdb_close(pDb);
  testCaseFinish(rc);
  *pRc = rc;
}