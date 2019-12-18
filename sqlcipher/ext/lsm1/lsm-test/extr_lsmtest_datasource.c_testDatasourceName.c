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
struct TYPE_3__ {scalar_t__ eType; int /*<<< orphan*/  nMaxVal; int /*<<< orphan*/  nMinVal; int /*<<< orphan*/  nMaxKey; int /*<<< orphan*/  nMinKey; } ;
typedef  TYPE_1__ DatasourceDefn ;

/* Variables and functions */
 scalar_t__ TEST_DATASOURCE_SEQUENCE ; 
 char* testMallocPrintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *testDatasourceName(const DatasourceDefn *p){
  char *zRet;
  zRet = testMallocPrintf("%s.(%d-%d).(%d-%d)",
      (p->eType==TEST_DATASOURCE_SEQUENCE ? "seq" : "rnd"),
      p->nMinKey, p->nMaxKey,
      p->nMinVal, p->nMaxVal
  );
  return zRet;
}