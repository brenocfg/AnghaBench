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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_7__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int member_0; int member_1; int member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ SetupStep ;
typedef  TYPE_2__ DatasourceDefn ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  ArraySize (TYPE_1__ const*) ; 
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 int /*<<< orphan*/  doSetupStepArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testDatasourceNew (TYPE_2__ const*) ; 

__attribute__((used)) static void setupDatabase1(TestDb *pDb, Datasource **ppData){
  const SetupStep aStep[] = {
    { 0,                                  1,     2000, 0, 0 },
    { 1,                                  0,     0, 0, 0 },
    { 0,                                  10001, 1000, 0, 0 },
  };
  const DatasourceDefn defn = {TEST_DATASOURCE_RANDOM, 12, 16, 100, 500};
  Datasource *pData;

  pData = testDatasourceNew(&defn);
  doSetupStepArray(pDb, pData, aStep, ArraySize(aStep));
  if( ppData ){
    *ppData = pData;
  }else{
    testDatasourceFree(pData);
  }
}