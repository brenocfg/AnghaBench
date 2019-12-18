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
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testFetchCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int*) ; 
 int /*<<< orphan*/  testFree (void*) ; 
 void* testMalloc (int) ; 
 int testPrngValue (int) ; 
 int /*<<< orphan*/  testScanCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,int,void*,int,int*) ; 

void testCompareDb(
  Datasource *pData,
  int nData,
  int iSeed,
  TestDb *pControl,
  TestDb *pDb,
  int *pRc
){
  int i;

  static int nCall = 0;
  nCall++;

  testScanCompare(pControl, pDb, 0, 0, 0,         0, 0,         pRc);
  testScanCompare(pControl, pDb, 1, 0, 0,         0, 0,         pRc);

  if( *pRc==0 ){
    int iKey1;
    int iKey2;
    void *pKey1; int nKey1;       /* Start key */
    void *pKey2; int nKey2;       /* Final key */

    iKey1 = testPrngValue(iSeed) % nData;
    iKey2 = testPrngValue(iSeed+1) % nData;
    testDatasourceEntry(pData, iKey1, &pKey2, &nKey1, 0, 0);
    pKey1 = testMalloc(nKey1+1);
    memcpy(pKey1, pKey2, nKey1+1);
    testDatasourceEntry(pData, iKey2, &pKey2, &nKey2, 0, 0);

    testScanCompare(pControl, pDb, 0, 0, 0,         pKey2, nKey2, pRc);
    testScanCompare(pControl, pDb, 0, pKey1, nKey1, 0, 0,         pRc);
    testScanCompare(pControl, pDb, 0, pKey1, nKey1, pKey2, nKey2, pRc);
    testScanCompare(pControl, pDb, 1, 0, 0,         pKey2, nKey2, pRc);
    testScanCompare(pControl, pDb, 1, pKey1, nKey1, 0, 0,         pRc);
    testScanCompare(pControl, pDb, 1, pKey1, nKey1, pKey2, nKey2, pRc);
    testFree(pKey1);
  }

  for(i=0; i<nData && *pRc==0; i++){
    void *pKey; int nKey;
    testDatasourceEntry(pData, i, &pKey, &nKey, 0, 0);
    testFetchCompare(pControl, pDb, pKey, nKey, pRc);
  }
}