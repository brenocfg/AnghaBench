#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int matchtype_t ;
struct TYPE_9__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_10__ {int ds_flags; int /*<<< orphan*/  ds_snapnames_zapobj; } ;
struct TYPE_8__ {TYPE_1__* dd_pool; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int DS_FLAG_CI_DATASET ; 
 int ENOTSUP ; 
 int MT_NORMALIZE ; 
 TYPE_5__* dsl_dataset_phys (TYPE_3__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ *) ; 
 int zap_lookup_norm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dsl_dataset_snap_lookup(dsl_dataset_t *ds, const char *name, uint64_t *value)
{
	objset_t *mos = ds->ds_dir->dd_pool->dp_meta_objset;
	uint64_t snapobj = dsl_dataset_phys(ds)->ds_snapnames_zapobj;
	matchtype_t mt = 0;
	int err;

	if (dsl_dataset_phys(ds)->ds_flags & DS_FLAG_CI_DATASET)
		mt = MT_NORMALIZE;

	err = zap_lookup_norm(mos, snapobj, name, 8, 1,
	    value, mt, NULL, 0, NULL);
	if (err == ENOTSUP && (mt & MT_NORMALIZE))
		err = zap_lookup(mos, snapobj, name, 8, 1, value);
	return (err);
}