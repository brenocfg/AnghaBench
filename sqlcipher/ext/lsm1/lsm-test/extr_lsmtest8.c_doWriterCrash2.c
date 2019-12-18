#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_7__ {int* aCksum; } ;
struct TYPE_6__ {int bWriter; TYPE_4__ hdr2; TYPE_4__ hdr1; } ;
typedef  TYPE_1__ ShmHeader ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int TEST_CKSUM_BYTES ; 
 int /*<<< orphan*/  doLiveRecovery (char*,char*,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  setupDatabase1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int tdb_lsm_open (char*,char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testBegin (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testCksumDatabase (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCommit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testFree (TYPE_1__*) ; 
 TYPE_1__* testMalloc (int) ; 
 int /*<<< orphan*/  testReadFile (char*,int /*<<< orphan*/ ,void*,int,int*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  testWriteFile (char*,int /*<<< orphan*/ ,void*,int,int*) ; 

__attribute__((used)) static void doWriterCrash2(int *pRc){
  int rc = 0;
  TestDb *pDb = 0;
  Datasource *pData = 0;

  rc = tdb_lsm_open("autowork=0", "testdb.lsm", 1, &pDb);
  if( rc==0 ){
    ShmHeader *pHdr1;
    ShmHeader *pHdr2;
    char zCksum1[TEST_CKSUM_BYTES];
    char zCksum2[TEST_CKSUM_BYTES];

    pHdr1 = testMalloc(sizeof(ShmHeader));
    pHdr2 = testMalloc(sizeof(ShmHeader));
    setupDatabase1(pDb, &pData);

    /* Grab a copy of the shared-memory header. And the db checksum */
    testReadFile("testdb.lsm-shm", 0, (void *)pHdr1, sizeof(ShmHeader), &rc);
    testCksumDatabase(pDb, zCksum1);

    /* Modify the database */
    testBegin(pDb, 2, &rc);
    testWriteDatasourceRange(pDb, pData, 30000, 200, &rc);
    testCommit(pDb, 0, &rc);

    /* Grab a second copy of the shared-memory header. And the db checksum */
    testReadFile("testdb.lsm-shm", 0, (void *)pHdr2, sizeof(ShmHeader), &rc);
    testCksumDatabase(pDb, zCksum2);
    doLiveRecovery("testdb.lsm", zCksum2, &rc);

    /* If both tree-headers are valid, tree-header-1 is used. */
    memcpy(&pHdr2->hdr1, &pHdr1->hdr1, sizeof(pHdr1->hdr1));
    pHdr2->bWriter = 1;
    testWriteFile("testdb.lsm-shm", 0, (void *)pHdr2, sizeof(ShmHeader), &rc);
    doLiveRecovery("testdb.lsm", zCksum1, &rc);

    /* If both tree-headers are valid, tree-header-1 is used. */
    memcpy(&pHdr2->hdr1, &pHdr2->hdr2, sizeof(pHdr1->hdr1));
    memcpy(&pHdr2->hdr2, &pHdr1->hdr1, sizeof(pHdr1->hdr1));
    pHdr2->bWriter = 1;
    testWriteFile("testdb.lsm-shm", 0, (void *)pHdr2, sizeof(ShmHeader), &rc);
    doLiveRecovery("testdb.lsm", zCksum2, &rc);

    /* If tree-header 1 is invalid, tree-header-2 is used */
    memcpy(&pHdr2->hdr2, &pHdr2->hdr1, sizeof(pHdr1->hdr1));
    pHdr2->hdr1.aCksum[0] = 5;
    pHdr2->hdr1.aCksum[0] = 6;
    pHdr2->bWriter = 1;
    testWriteFile("testdb.lsm-shm", 0, (void *)pHdr2, sizeof(ShmHeader), &rc);
    doLiveRecovery("testdb.lsm", zCksum2, &rc);

    /* If tree-header 2 is invalid, tree-header-1 is used */
    memcpy(&pHdr2->hdr1, &pHdr2->hdr2, sizeof(pHdr1->hdr1));
    pHdr2->hdr2.aCksum[0] = 5;
    pHdr2->hdr2.aCksum[0] = 6;
    pHdr2->bWriter = 1;
    testWriteFile("testdb.lsm-shm", 0, (void *)pHdr2, sizeof(ShmHeader), &rc);
    doLiveRecovery("testdb.lsm", zCksum2, &rc);

    testFree(pHdr1);
    testFree(pHdr2);
    testClose(&pDb);
  }

  *pRc = rc;
}