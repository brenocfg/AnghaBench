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
struct TYPE_3__ {int /*<<< orphan*/  bReopen; int /*<<< orphan*/  nRepeat; int /*<<< orphan*/  nRec; int /*<<< orphan*/  defn; } ;
typedef  TYPE_1__ Datatest4 ;

/* Variables and functions */
 char* testDatasourceName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 char* testMallocPrintf (char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *getName4(const char *zSystem, Datatest4 *pTest){
  char *zRet;
  char *zData;
  zData = testDatasourceName(&pTest->defn);
  zRet = testMallocPrintf("data4.%s.%s.%d.%d.%d", 
      zSystem, zData, pTest->nRec, pTest->nRepeat, pTest->bReopen
  );
  testFree(zData);
  return zRet;
}