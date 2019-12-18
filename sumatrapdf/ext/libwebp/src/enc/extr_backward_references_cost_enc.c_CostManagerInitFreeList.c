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
struct TYPE_4__ {int /*<<< orphan*/ * intervals_; int /*<<< orphan*/ * free_intervals_; } ;
typedef  TYPE_1__ CostManager ;

/* Variables and functions */
 int COST_MANAGER_MAX_FREE_LIST ; 
 int /*<<< orphan*/  CostIntervalAddToFreeList (TYPE_1__* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CostManagerInitFreeList(CostManager* const manager) {
  int i;
  manager->free_intervals_ = NULL;
  for (i = 0; i < COST_MANAGER_MAX_FREE_LIST; ++i) {
    CostIntervalAddToFreeList(manager, &manager->intervals_[i]);
  }
}