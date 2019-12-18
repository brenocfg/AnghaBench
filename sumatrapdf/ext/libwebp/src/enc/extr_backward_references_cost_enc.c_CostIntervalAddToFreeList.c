#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next_; } ;
struct TYPE_5__ {TYPE_2__* free_intervals_; } ;
typedef  TYPE_1__ CostManager ;
typedef  TYPE_2__ CostInterval ;

/* Variables and functions */

__attribute__((used)) static void CostIntervalAddToFreeList(CostManager* const manager,
                                      CostInterval* const interval) {
  interval->next_ = manager->free_intervals_;
  manager->free_intervals_ = interval;
}