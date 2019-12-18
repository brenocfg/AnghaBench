#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_5__ {int nFirst; int nLast; int nStep; char** azCksum; } ;
typedef  int /*<<< orphan*/  Datasource ;
typedef  TYPE_1__ CksumDb ;

/* Variables and functions */
 int TEST_CKSUM_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tdb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdb_open (char*,char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCksumDatabase (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 

CksumDb *testCksumArrayNew(
  Datasource *pData, 
  int nFirst, 
  int nLast, 
  int nStep
){
  TestDb *pDb;
  CksumDb *pRet;
  int i;
  int nEntry;
  int rc = 0;

  assert( nLast>=nFirst && ((nLast-nFirst)%nStep)==0 );
 
  pRet = malloc(sizeof(CksumDb));
  memset(pRet, 0, sizeof(CksumDb));
  pRet->nFirst = nFirst;
  pRet->nLast = nLast;
  pRet->nStep = nStep;
  nEntry = 1 + ((nLast - nFirst) / nStep);

  /* Allocate space so that azCksum is an array of nEntry pointers to
  ** buffers each TEST_CKSUM_BYTES in size.  */
  pRet->azCksum = (char **)malloc(nEntry * (sizeof(char *) + TEST_CKSUM_BYTES));
  for(i=0; i<nEntry; i++){
    char *pStart = (char *)(&pRet->azCksum[nEntry]);
    pRet->azCksum[i] = &pStart[i * TEST_CKSUM_BYTES];
  }

  tdb_open("lsm", "tempdb.lsm", 1, &pDb);
  testWriteDatasourceRange(pDb, pData, 0, nFirst, &rc);
  for(i=0; i<nEntry; i++){
    testCksumDatabase(pDb, pRet->azCksum[i]);
    if( i==nEntry ) break;
    testWriteDatasourceRange(pDb, pData, nFirst+i*nStep, nStep, &rc);
  }

  tdb_close(pDb);

  return pRet;
}