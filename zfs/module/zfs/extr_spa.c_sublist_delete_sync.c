#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * to_free; int /*<<< orphan*/  key; int /*<<< orphan*/ * ll; int /*<<< orphan*/ * spa; } ;
typedef  TYPE_1__ sublist_delete_arg_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dsl_deadlist_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  bplist_t ;

/* Variables and functions */
 int /*<<< orphan*/  bplist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_blkptr_cb ; 
 int /*<<< orphan*/  dsl_deadlist_remove_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sublist_delete_sync(void *arg, dmu_tx_t *tx)
{
	sublist_delete_arg_t *sda = arg;
	spa_t *spa = sda->spa;
	dsl_deadlist_t *ll = sda->ll;
	uint64_t key = sda->key;
	bplist_t *to_free = sda->to_free;

	bplist_iterate(to_free, delete_blkptr_cb, spa, tx);
	dsl_deadlist_remove_entry(ll, key, tx);
}