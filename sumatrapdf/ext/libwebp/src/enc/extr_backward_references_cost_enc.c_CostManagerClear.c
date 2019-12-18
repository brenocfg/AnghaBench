#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * recycled_intervals_; int /*<<< orphan*/ * head_; int /*<<< orphan*/  cache_intervals_; int /*<<< orphan*/  costs_; } ;
typedef  TYPE_1__ CostManager ;

/* Variables and functions */
 int /*<<< orphan*/  CostManagerInitFreeList (TYPE_1__* const) ; 
 int /*<<< orphan*/  DeleteIntervalList (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CostManagerClear(CostManager* const manager) {
  if (manager == NULL) return;

  WebPSafeFree(manager->costs_);
  WebPSafeFree(manager->cache_intervals_);

  // Clear the interval lists.
  DeleteIntervalList(manager, manager->head_);
  manager->head_ = NULL;
  DeleteIntervalList(manager, manager->recycled_intervals_);
  manager->recycled_intervals_ = NULL;

  // Reset pointers, count_ and cache_intervals_size_.
  memset(manager, 0, sizeof(*manager));
  CostManagerInitFreeList(manager);
}