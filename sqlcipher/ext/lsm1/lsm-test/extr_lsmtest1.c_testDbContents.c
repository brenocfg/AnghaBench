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
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int tdb_write (int /*<<< orphan*/ *,void*,int,void*,int) ; 
 int testControlDb (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,void**,int*) ; 
 int /*<<< orphan*/  testFetch (int /*<<< orphan*/ *,void*,int,void*,int,int*) ; 
 int /*<<< orphan*/  testFree (void*) ; 
 void* testMalloc (int) ; 
 int testPrngValue (int) ; 
 int /*<<< orphan*/  testScanCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,int,void*,int,int*) ; 

void testDbContents(
  TestDb *pDb,                    /* Database handle being tested */
  Datasource *pData,              /* pDb contains data from here */
  int nRow,                       /* Size of key domain */
  int iFirst,                     /* Index of first key from pData in pDb */
  int iLast,                      /* Index of last key from pData in pDb */
  int nLookupTest,                /* Number of lookup tests to run */
  int nScanTest,                  /* Number of scan tests to run */
  int *pRc                        /* IN/OUT: Error code */
){
  int j;
  int rc = *pRc;

  if( rc==0 && nScanTest ){
    TestDb *pDb2 = 0;

    /* Open a control db (i.e. one that we assume works) */
    rc = testControlDb(&pDb2);

    for(j=iFirst; rc==0 && j<=iLast; j++){
      void *pKey; int nKey;         /* Database key to insert */
      void *pVal; int nVal;         /* Database value to insert */
      testDatasourceEntry(pData, j, &pKey, &nKey, &pVal, &nVal);
      rc = tdb_write(pDb2, pKey, nKey, pVal, nVal);
    }

    if( rc==0 ){
      int iKey1;
      int iKey2;
      void *pKey1; int nKey1;       /* Start key */
      void *pKey2; int nKey2;       /* Final key */

      iKey1 = testPrngValue((iFirst<<8) + (iLast<<16)) % nRow;
      iKey2 = testPrngValue((iLast<<8) + (iFirst<<16)) % nRow;
      testDatasourceEntry(pData, iKey1, &pKey2, &nKey1, 0, 0);
      pKey1 = testMalloc(nKey1+1);
      memcpy(pKey1, pKey2, nKey1+1);
      testDatasourceEntry(pData, iKey2, &pKey2, &nKey2, 0, 0);

      testScanCompare(pDb2, pDb, 0, 0, 0,         0, 0,         &rc);
      testScanCompare(pDb2, pDb, 0, 0, 0,         pKey2, nKey2, &rc);
      testScanCompare(pDb2, pDb, 0, pKey1, nKey1, 0, 0,         &rc);
      testScanCompare(pDb2, pDb, 0, pKey1, nKey1, pKey2, nKey2, &rc);
      testScanCompare(pDb2, pDb, 1, 0, 0,         0, 0,         &rc);
      testScanCompare(pDb2, pDb, 1, 0, 0,         pKey2, nKey2, &rc);
      testScanCompare(pDb2, pDb, 1, pKey1, nKey1, 0, 0,         &rc);
      testScanCompare(pDb2, pDb, 1, pKey1, nKey1, pKey2, nKey2, &rc);
      testFree(pKey1);
    }
    tdb_close(pDb2);
  }

  /* Test some lookups. */
  for(j=0; rc==0 && j<nLookupTest; j++){
    int iKey;                     /* Datasource key to test */
    void *pKey; int nKey;         /* Database key to query for */
    void *pVal; int nVal;         /* Expected result of query */

    if( nLookupTest>=nRow ){
      iKey = j;
    }else{
      iKey = testPrngValue(j + (iFirst<<8) + (iLast<<16)) % nRow;
    }

    testDatasourceEntry(pData, iKey, &pKey, &nKey, &pVal, &nVal);
    if( iFirst>iKey || iKey>iLast ){
      pVal = 0;
      nVal = -1;
    }

    testFetch(pDb, pKey, nKey, pVal, nVal, &rc);
  }

  *pRc = rc;
}