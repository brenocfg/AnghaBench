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
struct TYPE_3__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DatasourceDefn ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 char* getName (char const*) ; 
 int rollback_test_1 (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_1__*) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 int testGlobMatch (char const*,char*) ; 

void test_rollback(
  const char *zSystem, 
  const char *zPattern, 
  int *pRc
){
  if( *pRc==0 ){
    int bRun = 1;

    if( zPattern ){
      char *zName = getName(zSystem);
      bRun = testGlobMatch(zPattern, zName);
      testFree(zName);
    }

    if( bRun ){
      DatasourceDefn defn = { TEST_DATASOURCE_RANDOM, 10, 15, 50, 100 };
      Datasource *pData = testDatasourceNew(&defn);
      *pRc = rollback_test_1(zSystem, pData);
      testDatasourceFree(pData);
    }
  }
}