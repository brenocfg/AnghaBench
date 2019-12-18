#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_4__ {struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ Level ;

/* Variables and functions */
 int /*<<< orphan*/  sortedFreeLevel (int /*<<< orphan*/ *,TYPE_1__*) ; 

void lsmSortedFreeLevel(lsm_env *pEnv, Level *pLevel){
  Level *pNext;
  Level *p;

  for(p=pLevel; p; p=pNext){
    pNext = p->pNext;
    sortedFreeLevel(pEnv, p);
  }
}