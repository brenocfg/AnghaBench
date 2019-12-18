#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {scalar_t__ ub_checkpoint_txg; } ;
typedef  TYPE_1__ uberblock_t ;
struct TYPE_10__ {int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_ZPOOL_CHECKPOINT ; 
 int ENOENT ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  dump_leftover_checkpoint_blocks (TYPE_2__*) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  dump_uberblock (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spa_feature_is_active (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_checkpoint_blocks (TYPE_2__*) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 

__attribute__((used)) static int
verify_checkpoint(spa_t *spa)
{
	uberblock_t checkpoint;
	int error;

	if (!spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT))
		return (0);

	error = zap_lookup(spa->spa_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_ZPOOL_CHECKPOINT, sizeof (uint64_t),
	    sizeof (uberblock_t) / sizeof (uint64_t), &checkpoint);

	if (error == ENOENT && !dump_opt['L']) {
		/*
		 * If the feature is active but the uberblock is missing
		 * then we must be in the middle of discarding the
		 * checkpoint.
		 */
		(void) printf("\nPartially discarded checkpoint "
		    "state found:\n");
		if (dump_opt['m'] > 3)
			dump_leftover_checkpoint_blocks(spa);
		return (0);
	} else if (error != 0) {
		(void) printf("lookup error %d when looking for "
		    "checkpointed uberblock in MOS\n", error);
		return (error);
	}
	dump_uberblock(&checkpoint, "\nCheckpointed uberblock found:\n", "\n");

	if (checkpoint.ub_checkpoint_txg == 0) {
		(void) printf("\nub_checkpoint_txg not set in checkpointed "
		    "uberblock\n");
		error = 3;
	}

	if (error == 0 && !dump_opt['L'])
		verify_checkpoint_blocks(spa);

	return (error);
}