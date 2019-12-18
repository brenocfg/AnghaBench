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
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdb_lsm_prepare_sync_crash (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testCaseNDot () ; 
 int /*<<< orphan*/  testCaseProgress (int,int const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testCksumArrayFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCksumArrayGet (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * testCksumArrayNew (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  testCompareCksumLsmdb (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * testOpen (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testRestoreDb (char const*,char*) ; 
 int /*<<< orphan*/  testSetupSavedLsmdb (char*,char const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 

__attribute__((used)) static void crash_test3(int bCompress, int *pRc){
  const char *DBNAME = "testdb.lsm";
  const int nIter = 100;
  const DatasourceDefn defn = {TEST_DATASOURCE_RANDOM, 12, 16, 1000, 1000};

  int i;
  int iDot = 0;
  Datasource *pData;
  CksumDb *pCksumDb;
  TestDb *pDb;

  /* Allocate datasource. And calculate the expected checksums. */
  pData = testDatasourceNew(&defn);
  pCksumDb = testCksumArrayNew(pData, 110, 150, 10);

  /* Setup and save the initial database. */
  testSetupSavedLsmdb("", DBNAME, pData, 100, pRc);

  for(i=0; i<nIter && *pRc==0; i++){
    int iOpen;
    testCaseProgress(i, nIter, testCaseNDot(), &iDot);
    testRestoreDb(DBNAME, "log");

    for(iOpen=0; iOpen<5; iOpen++){
      /* Open the database. Insert 10 more records. */
      pDb = testOpen("lsm", 0, pRc);
      testWriteDatasourceRange(pDb, pData, 100+iOpen*10, 10, pRc);

      /* Schedule a crash simulation then close the db. */
      tdb_lsm_prepare_sync_crash(pDb, 1 + (i%2));
      tdb_close(pDb);

      /* Open the database and check that the crash did not cause any
      ** data loss.  */
      testCompareCksumLsmdb(DBNAME, bCompress,
        testCksumArrayGet(pCksumDb, 110 + iOpen*10), 0,
        pRc
      );
    }
  }

  testDatasourceFree(pData);
  testCksumArrayFree(pCksumDb);
}