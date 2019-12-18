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
typedef  int /*<<< orphan*/  zdb_cb_t ;
struct TYPE_3__ {int /*<<< orphan*/  dle_bpobj; } ;
typedef  TYPE_1__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  bplist_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bplist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bplist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bplist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_block_cb ; 
 int /*<<< orphan*/  dsl_process_sub_livelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
livelist_entry_count_blocks_cb(void *args, dsl_deadlist_entry_t *dle)
{
	zdb_cb_t *zbc = args;
	bplist_t blks;
	bplist_create(&blks);
	/* determine which blocks have been alloc'd but not freed */
	VERIFY0(dsl_process_sub_livelist(&dle->dle_bpobj, &blks, NULL, NULL));
	/* count those blocks */
	(void) bplist_iterate(&blks, count_block_cb, zbc, NULL);
	bplist_destroy(&blks);
	return (0);
}