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
struct TYPE_3__ {int /*<<< orphan*/  nVerify; int /*<<< orphan*/  nRow; int /*<<< orphan*/  defn; } ;
typedef  TYPE_1__ Datatest1 ;

/* Variables and functions */
 char* testDatasourceName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 char* testMallocPrintf (char*,char const*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *getName(const char *zSystem, int bRecover, Datatest1 *pTest){
  char *zRet;
  char *zData;
  zData = testDatasourceName(&pTest->defn);
  zRet = testMallocPrintf("data.%s.%s.rec=%d.%d.%d", 
      zSystem, zData, bRecover, pTest->nRow, pTest->nVerify
  );
  testFree(zData);
  return zRet;
}