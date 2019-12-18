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
struct TYPE_3__ {int /*<<< orphan*/  nValMax; int /*<<< orphan*/  nValMin; int /*<<< orphan*/  nDelete; int /*<<< orphan*/  nWrite; int /*<<< orphan*/  nIter; int /*<<< orphan*/  nRange; } ;
typedef  TYPE_1__ Datatest3 ;

/* Variables and functions */
 char* testMallocPrintf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *getName3(const char *zSystem, Datatest3 *p){
  return testMallocPrintf("data3.%s.%d.%d.%d.%d.(%d..%d)",
      zSystem, p->nRange, p->nIter, p->nWrite, p->nDelete, 
      p->nValMin, p->nValMax
  );
}