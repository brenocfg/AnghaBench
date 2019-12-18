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
typedef  int /*<<< orphan*/  TestDb ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int TEST_CKSUM_BYTES ; 
 int /*<<< orphan*/  doLiveRecovery (char*,char*,int*) ; 
 int /*<<< orphan*/  setupDatabase1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int tdb_lsm_open (char*,char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testBegin (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testCaseNDot () ; 
 int /*<<< orphan*/  testCaseProgress (int,int const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testCksumDatabase (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCommit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int const,int*) ; 

__attribute__((used)) static void doWriterCrash1(int *pRc){
  const int nWrite = 2000;
  const int nStep = 10;
  const int iWriteStart = 20000;
  int rc = 0;
  TestDb *pDb = 0;
  Datasource *pData = 0;

  rc = tdb_lsm_open("autowork=0", "testdb.lsm", 1, &pDb);
  if( rc==0 ){
    int iDot = 0;
    char zCksum[TEST_CKSUM_BYTES];
    int i;
    setupDatabase1(pDb, &pData);
    testCksumDatabase(pDb, zCksum);
    testBegin(pDb, 2, &rc);
    for(i=0; rc==0 && i<nWrite; i+=nStep){
      testCaseProgress(i, nWrite, testCaseNDot(), &iDot);
      testWriteDatasourceRange(pDb, pData, iWriteStart+i, nStep, &rc);
      doLiveRecovery("testdb.lsm", zCksum, &rc);
    }
  }
  testCommit(pDb, 0, &rc);
  testClose(&pDb);
  testDatasourceFree(pData);
  *pRc = rc;
}