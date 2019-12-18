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

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 int /*<<< orphan*/  do_test_api1_lsm (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tdb_lsm (int /*<<< orphan*/ *) ; 
 scalar_t__ testCaseBegin (int*,char const*,char*) ; 
 int /*<<< orphan*/  testCaseFinish (int) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * testOpen (char*,int,int*) ; 
 int /*<<< orphan*/  testWriteDatasourceRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void do_test_api1(const char *zPattern, int *pRc){
  if( testCaseBegin(pRc, zPattern, "api1.lsm") ){
    const DatasourceDefn defn = { TEST_DATASOURCE_RANDOM, 10, 15, 200, 250 };
    Datasource *pData;
    TestDb *pDb;
    int rc = 0;

    pDb = testOpen("lsm_lomem", 1, &rc);
    pData = testDatasourceNew(&defn);
    testWriteDatasourceRange(pDb, pData, 0, 1000, pRc);

    do_test_api1_lsm(tdb_lsm(pDb), pRc);

    testDatasourceFree(pData);
    testClose(&pDb);

    testCaseFinish(*pRc);
  }
}