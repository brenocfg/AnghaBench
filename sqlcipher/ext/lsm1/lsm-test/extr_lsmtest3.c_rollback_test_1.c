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
typedef  int /*<<< orphan*/  CksumDb ;

/* Variables and functions */
 int TEST_CKSUM_BYTES ; 
 char* getName (char const*) ; 
 int /*<<< orphan*/  tdb_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdb_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tdb_open (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tdb_rollback (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tdb_transaction_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCaseFinish (int) ; 
 int /*<<< orphan*/  testCaseSkip () ; 
 int /*<<< orphan*/  testCaseStart (int*,char*) ; 
 int /*<<< orphan*/  testCksumArrayFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCksumArrayGet (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * testCksumArrayNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  testCksumDatabase (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  testCompareInt (int,int,int*) ; 
 int /*<<< orphan*/  testCompareStr (char*,int /*<<< orphan*/ ,int*) ; 
 int testCountDatabase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 

__attribute__((used)) static int rollback_test_1(
  const char *zSystem,
  Datasource *pData
){
  const int nRepeat = 100;

  TestDb *pDb;
  int rc;
  int i;
  CksumDb *pCksum;
  char *zName;

  zName = getName(zSystem);
  testCaseStart(&rc, zName);
  testFree(zName);

  pCksum = testCksumArrayNew(pData, 0, nRepeat*100, 100);
  pDb = 0;
  rc = tdb_open(zSystem, 0, 1, &pDb);
  if( pDb && tdb_transaction_support(pDb)==0 ){
    testCaseSkip();
    goto skip_rollback_test;
  }

  for(i=0; i<nRepeat && rc==0; i++){
    char zCksum[TEST_CKSUM_BYTES];
    int nCurrent = (((i+1)/2) * 100);
    int nDbRow;
    int iTrans;

    /* Check that the database is the expected size. */
    nDbRow = testCountDatabase(pDb);
    testCompareInt(nCurrent, nDbRow, &rc);

    for(iTrans=2; iTrans<=6 && rc==0; iTrans++){
      tdb_begin(pDb, iTrans);
      testWriteDatasourceRange(pDb, pData, nCurrent, 100, &rc);
      nCurrent += 100;
    }

    testCksumDatabase(pDb, zCksum);
    testCompareStr(zCksum, testCksumArrayGet(pCksum, nCurrent), &rc);

    for(iTrans=6; iTrans>2 && rc==0; iTrans--){
      tdb_rollback(pDb, iTrans);
      nCurrent -= 100;
      testCksumDatabase(pDb, zCksum);
      testCompareStr(zCksum, testCksumArrayGet(pCksum, nCurrent), &rc);
    }

    if( i%2 ){
      tdb_rollback(pDb, 0);
      nCurrent -= 100;
      testCksumDatabase(pDb, zCksum);
      testCompareStr(zCksum, testCksumArrayGet(pCksum, nCurrent), &rc);
    }else{
      tdb_commit(pDb, 0);
    }
  }
  testCaseFinish(rc);

 skip_rollback_test:
  tdb_close(pDb);
  testCksumArrayFree(pCksum);
  return rc;
}