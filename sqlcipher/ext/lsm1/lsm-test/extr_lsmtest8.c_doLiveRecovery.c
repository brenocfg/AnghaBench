#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_7__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdr2; int /*<<< orphan*/  hdr1; } ;
typedef  TYPE_1__ ShmHeader ;
typedef  TYPE_2__ DatasourceDefn ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_CONFIG_AUTOFLUSH ; 
 int LSM_OK ; 
 int TEST_CKSUM_BYTES ; 
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 TYPE_1__* getShmHeader (char const*) ; 
 int /*<<< orphan*/  lsm_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lsm_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int lsm_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tdb_lsm (int /*<<< orphan*/ *) ; 
 int tdb_lsm_open (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCksumDatabase (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCompareStr (char const*,char*,int*) ; 
 int /*<<< orphan*/  testCopyLsmdb (char const*,char const*) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_2__ const*) ; 
 int /*<<< orphan*/  testDeleteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  testDeleteLsmdb (char const*) ; 
 int /*<<< orphan*/  testFree (TYPE_1__*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 

__attribute__((used)) static void doLiveRecovery(const char *zDb, const char *zCksum, int *pRc){
  if( *pRc==LSM_OK ){
    const DatasourceDefn defn = {TEST_DATASOURCE_RANDOM, 20, 25, 100, 500};
    Datasource *pData;
    const char *zCopy = "testcopy.lsm";
    char zCksum2[TEST_CKSUM_BYTES];
    TestDb *pDb = 0;
    int rc;

    pData = testDatasourceNew(&defn);

    testCopyLsmdb(zDb, zCopy);
    rc = tdb_lsm_open("test_no_recovery=1", zCopy, 0, &pDb);
    if( rc==0 ){
      ShmHeader *pHdr;
      lsm_db *db;
      testCksumDatabase(pDb, zCksum2);
      testCompareStr(zCksum, zCksum2, &rc);

      testWriteDatasourceRange(pDb, pData, 1, 10, &rc);
      testDeleteDatasourceRange(pDb, pData, 1, 10, &rc);

      /* Test that the two tree-headers are now consistent. */
      pHdr = getShmHeader(zCopy);
      if( rc==0 && memcmp(&pHdr->hdr1, &pHdr->hdr2, sizeof(pHdr->hdr1)) ){
        rc = 1;
      }
      testFree(pHdr);

      if( rc==0 ){
        int nBuf = 64;
        db = tdb_lsm(pDb);
        lsm_config(db, LSM_CONFIG_AUTOFLUSH, &nBuf);
        lsm_begin(db, 1);
        lsm_commit(db, 0);
        rc = lsm_work(db, 0, 0, 0);
      }

      testCksumDatabase(pDb, zCksum2);
      testCompareStr(zCksum, zCksum2, &rc);
    }

    testDatasourceFree(pData);
    testClose(&pDb);
    testDeleteLsmdb(zCopy);
    *pRc = rc;
  }
}