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
struct TYPE_3__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DatasourceDefn ;
typedef  int /*<<< orphan*/  Datasource ;
typedef  int /*<<< orphan*/  CksumDb ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int tdb_lsm_open (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tdb_lsm_prepare_sync_crash (int /*<<< orphan*/ *,int) ; 
 int tdb_write (int /*<<< orphan*/ *,void*,int,void*,int) ; 
 int /*<<< orphan*/  testCaseNDot () ; 
 int /*<<< orphan*/  testCaseProgress (int,int const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testCksumArrayFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCksumArrayGet (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * testCksumArrayNew (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  testCompareCksumLsmdb (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,void**,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_1__ const*) ; 
 int /*<<< orphan*/  testRestoreDb (char const*,char*) ; 
 int /*<<< orphan*/  testSetupSavedLsmdb (char*,char const*,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void crash_test2(int bCompress, int *pRc){
  const char *DBNAME = "testdb.lsm";
  const DatasourceDefn defn = {TEST_DATASOURCE_RANDOM, 12, 16, 1000, 1000};

  const int nIter = 200;
  const int nInsert = 20;

  int i;
  int iDot = 0;
  Datasource *pData;
  CksumDb *pCksumDb;
  TestDb *pDb;

  /* Allocate datasource. And calculate the expected checksums. */
  pData = testDatasourceNew(&defn);
  pCksumDb = testCksumArrayNew(pData, 100, 100+nInsert, 1);

  /* Setup and save the initial database. */
  testSetupSavedLsmdb("", DBNAME, pData, 100, pRc);

  for(i=0; i<nIter && *pRc==0; i++){
    int iIns;
    int testrc = 0;

    testCaseProgress(i, nIter, testCaseNDot(), &iDot);

    /* Restore and open the database. */
    testRestoreDb(DBNAME, "log");
    testrc = tdb_lsm_open("safety=2", DBNAME, 0, &pDb);
    assert( testrc==0 );

    /* Insert nInsert records into the database. Crash midway through. */
    tdb_lsm_prepare_sync_crash(pDb, 1 + (i%(nInsert+2)));
    for(iIns=0; iIns<nInsert; iIns++){
      void *pKey; int nKey;
      void *pVal; int nVal;

      testDatasourceEntry(pData, 100+iIns, &pKey, &nKey, &pVal, &nVal);
      testrc = tdb_write(pDb, pKey, nKey, pVal, nVal);
      if( testrc ) break;
    }
    tdb_close(pDb);

    /* Check that no data was lost when the system crashed. */
    testCompareCksumLsmdb(DBNAME, bCompress,
      testCksumArrayGet(pCksumDb, 100 + iIns),
      testCksumArrayGet(pCksumDb, 100 + iIns + 1),
      pRc
    );
  }

  testDatasourceFree(pData);
  testCksumArrayFree(pCksumDb);
}