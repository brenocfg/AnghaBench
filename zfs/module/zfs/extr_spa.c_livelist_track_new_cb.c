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
struct TYPE_2__ {int /*<<< orphan*/  allocs; int /*<<< orphan*/  frees; } ;
typedef  TYPE_1__ livelist_new_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bplist_append (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zfs_livelist_condense_new_alloc ; 

__attribute__((used)) static int
livelist_track_new_cb(void *arg, const blkptr_t *bp, boolean_t bp_freed,
    dmu_tx_t *tx)
{
	ASSERT(tx == NULL);
	livelist_new_arg_t *lna = arg;
	if (bp_freed) {
		bplist_append(lna->frees, bp);
	} else {
		bplist_append(lna->allocs, bp);
		zfs_livelist_condense_new_alloc++;
	}
	return (0);
}