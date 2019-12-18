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
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_3__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DatasourceDefn ;
typedef  int /*<<< orphan*/  Datasource ;
typedef  int /*<<< orphan*/  CksumDb ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsm_checkpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lsm_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int*) ; 
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tdb_lsm (int /*<<< orphan*/ *) ; 
 int tdb_lsm_open (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tdb_lsm_prepare_sync_crash (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testCaseNDot () ; 
 int /*<<< orphan*/  testCaseProgress (int,int const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testCksumArrayFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCksumArrayGet (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/ * testCksumArrayNew (int /*<<< orphan*/ *,int const,int const,int) ; 
 int /*<<< orphan*/  testCompareCksumLsmdb (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_1__ const*) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 char* testMallocPrintf (char*,char const*) ; 
 int /*<<< orphan*/  testRestoreDb (char const*,char*) ; 
 int /*<<< orphan*/  testSetupSavedLsmdb (char*,char const*,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void crash_test1(int bCompress, int *pRc){
  const char *DBNAME = "testdb.lsm";
  const DatasourceDefn defn = {TEST_DATASOURCE_RANDOM, 12, 16, 200, 200};

  const int nRow = 5000;          /* Database size */
  const int nIter = 200;          /* Number of test iterations */
  const int nWork = 20;           /* Maximum lsm_work() calls per iteration */
  const int nPage = 15;           /* Pages per lsm_work call */

  int i;
  int iDot = 0;
  Datasource *pData;
  CksumDb *pCksumDb;
  TestDb *pDb;
  char *zCfg;

  const char *azConfig[2] = {
    "page_size=1024 block_size=65536 autoflush=16384 safety=2 mmap=0", 
    "page_size=1024 block_size=65536 autoflush=16384 safety=2 "
    " compression=1 mmap=0"
  };
  assert( bCompress==0 || bCompress==1 );

  /* Allocate datasource. And calculate the expected checksums. */
  pData = testDatasourceNew(&defn);
  pCksumDb = testCksumArrayNew(pData, nRow, nRow, 1);

  /* Setup and save the initial database. */

  zCfg = testMallocPrintf("%s automerge=7", azConfig[bCompress]);
  testSetupSavedLsmdb(zCfg, DBNAME, pData, 5000, pRc);
  testFree(zCfg);

  for(i=0; i<nIter && *pRc==0; i++){
    int iWork;
    int testrc = 0;

    testCaseProgress(i, nIter, testCaseNDot(), &iDot);

    /* Restore and open the database. */
    testRestoreDb(DBNAME, "log");
    testrc = tdb_lsm_open(azConfig[bCompress], DBNAME, 0, &pDb);
    assert( testrc==0 );

    /* Call lsm_work() on the db */
    tdb_lsm_prepare_sync_crash(pDb, 1 + (i%(nWork*2)));
    for(iWork=0; testrc==0 && iWork<nWork; iWork++){
      int nWrite = 0;
      lsm_db *db = tdb_lsm(pDb);
      testrc = lsm_work(db, 0, nPage, &nWrite);
      /* assert( testrc!=0 || nWrite>0 ); */
      if( testrc==0 ) testrc = lsm_checkpoint(db, 0);
    }
    tdb_close(pDb);

    /* Check that the database content is still correct */
    testCompareCksumLsmdb(DBNAME, 
        bCompress, testCksumArrayGet(pCksumDb, nRow), 0, pRc);
  }

  testCksumArrayFree(pCksumDb);
  testDatasourceFree(pData);
}