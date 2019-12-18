#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_bookmarks; TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_8__ {int /*<<< orphan*/  zbm_creation_txg; } ;
struct TYPE_10__ {TYPE_2__ dbn_phys; } ;
typedef  TYPE_4__ dsl_bookmark_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_4__* avl_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ ) ; 

uint64_t
dsl_bookmark_latest_txg(dsl_dataset_t *ds)
{
	ASSERT(dsl_pool_config_held(ds->ds_dir->dd_pool));
	dsl_bookmark_node_t *dbn = avl_last(&ds->ds_bookmarks);
	if (dbn == NULL)
		return (0);
	return (dbn->dbn_phys.zbm_creation_txg);
}