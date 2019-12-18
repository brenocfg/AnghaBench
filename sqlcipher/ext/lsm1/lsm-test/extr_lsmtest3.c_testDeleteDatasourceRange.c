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
 int /*<<< orphan*/  testDeleteDatasource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

void testDeleteDatasourceRange(
  TestDb *pDb,                    /* Database to write to */
  Datasource *pData,              /* Data source to read keys from */
  int iFirst,                     /* Index of first key */
  int nWrite,                     /* Number of keys to delete */
  int *pRc                        /* IN/OUT: Error code */
){
  int i;
  for(i=0; i<nWrite; i++){
    testDeleteDatasource(pDb, pData, iFirst+i, pRc);
  }
}