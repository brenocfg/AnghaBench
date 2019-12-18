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
 int /*<<< orphan*/  testDatasourceEntry (int /*<<< orphan*/ *,int,void**,int*,void**,int*) ; 
 int /*<<< orphan*/  testWrite (int /*<<< orphan*/ *,void*,int,void*,int,int*) ; 

void testWriteDatasource(TestDb *pDb, Datasource *pData, int i, int *pRc){
  void *pKey; int nKey;
  void *pVal; int nVal;
  testDatasourceEntry(pData, i, &pKey, &nKey, &pVal, &nVal);
  testWrite(pDb, pKey, nKey, pVal, nVal, pRc);
}