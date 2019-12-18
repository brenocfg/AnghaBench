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
typedef  int uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  dn_mtx; int /*<<< orphan*/ ** dn_free_ranges; scalar_t__ dn_free_txg; TYPE_1__* dn_objset; } ;
typedef  TYPE_2__ dnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  os_spa; } ;

/* Variables and functions */
 int DMU_BONUS_BLKID ; 
 int DMU_SPILL_BLKID ; 
 int FALSE ; 
 int TRUE ; 
 int TXG_SIZE ; 
 int dnode_spill_freed (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ range_tree_contains (int /*<<< orphan*/ *,int,int) ; 
 void* spa_get_dsl (int /*<<< orphan*/ ) ; 

uint64_t
dnode_block_freed(dnode_t *dn, uint64_t blkid)
{
	void *dp = spa_get_dsl(dn->dn_objset->os_spa);
	int i;

	if (blkid == DMU_BONUS_BLKID)
		return (FALSE);

	/*
	 * If we're in the process of opening the pool, dp will not be
	 * set yet, but there shouldn't be anything dirty.
	 */
	if (dp == NULL)
		return (FALSE);

	if (dn->dn_free_txg)
		return (TRUE);

	if (blkid == DMU_SPILL_BLKID)
		return (dnode_spill_freed(dn));

	mutex_enter(&dn->dn_mtx);
	for (i = 0; i < TXG_SIZE; i++) {
		if (dn->dn_free_ranges[i] != NULL &&
		    range_tree_contains(dn->dn_free_ranges[i], blkid, 1))
			break;
	}
	mutex_exit(&dn->dn_mtx);
	return (i < TXG_SIZE);
}