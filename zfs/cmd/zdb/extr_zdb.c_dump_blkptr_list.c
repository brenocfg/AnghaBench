#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uncomp ;
typedef  scalar_t__ uint64_t ;
struct TYPE_13__ {TYPE_1__* spa_dsl_pool; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  entries ;
struct TYPE_15__ {scalar_t__ bpo_object; } ;
struct TYPE_14__ {int /*<<< orphan*/  dl_tree; TYPE_2__* dl_phys; TYPE_5__ dl_bpobj; scalar_t__ dl_oldfmt; int /*<<< orphan*/  dl_object; int /*<<< orphan*/  dl_os; } ;
typedef  TYPE_4__ dsl_deadlist_t ;
typedef  int /*<<< orphan*/  comp ;
typedef  int /*<<< orphan*/  bytes ;
struct TYPE_12__ {int /*<<< orphan*/  dl_uncomp; int /*<<< orphan*/  dl_comp; int /*<<< orphan*/  dl_used; } ;
struct TYPE_11__ {scalar_t__ dp_empty_bpobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int NN_NUMBUF_SZ ; 
 int /*<<< orphan*/  avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_count_refd (TYPE_5__*) ; 
 TYPE_3__* dmu_objset_spa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_deadlist_entry_count_refd ; 
 int /*<<< orphan*/  dsl_deadlist_entry_dump ; 
 int /*<<< orphan*/  dsl_deadlist_iterate (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dump_full_bpobj (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  mos_obj_refd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  zdb_nicenum (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
dump_blkptr_list(dsl_deadlist_t *dl, char *name)
{
	char bytes[32];
	char comp[32];
	char uncomp[32];
	char entries[32];
	spa_t *spa = dmu_objset_spa(dl->dl_os);
	uint64_t empty_bpobj = spa->spa_dsl_pool->dp_empty_bpobj;

	if (dl->dl_oldfmt) {
		if (dl->dl_bpobj.bpo_object != empty_bpobj)
			bpobj_count_refd(&dl->dl_bpobj);
	} else {
		mos_obj_refd(dl->dl_object);
		dsl_deadlist_iterate(dl, dsl_deadlist_entry_count_refd, spa);
	}

	/* make sure nicenum has enough space */
	CTASSERT(sizeof (bytes) >= NN_NUMBUF_SZ);
	CTASSERT(sizeof (comp) >= NN_NUMBUF_SZ);
	CTASSERT(sizeof (uncomp) >= NN_NUMBUF_SZ);
	CTASSERT(sizeof (entries) >= NN_NUMBUF_SZ);

	if (dump_opt['d'] < 3)
		return;

	if (dl->dl_oldfmt) {
		dump_full_bpobj(&dl->dl_bpobj, "old-format deadlist", 0);
		return;
	}

	zdb_nicenum(dl->dl_phys->dl_used, bytes, sizeof (bytes));
	zdb_nicenum(dl->dl_phys->dl_comp, comp, sizeof (comp));
	zdb_nicenum(dl->dl_phys->dl_uncomp, uncomp, sizeof (uncomp));
	zdb_nicenum(avl_numnodes(&dl->dl_tree), entries, sizeof (entries));
	(void) printf("\n    %s: %s (%s/%s comp), %s entries\n",
	    name, bytes, comp, uncomp, entries);

	if (dump_opt['d'] < 4)
		return;

	(void) printf("\n");

	dsl_deadlist_iterate(dl, dsl_deadlist_entry_dump, NULL);
}