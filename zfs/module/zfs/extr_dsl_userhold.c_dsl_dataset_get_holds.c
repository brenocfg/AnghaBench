#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_14__ {int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_15__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
struct TYPE_16__ {scalar_t__ ds_userrefs_obj; } ;
struct TYPE_13__ {TYPE_1__* dd_pool; } ;
struct TYPE_12__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_4__**) ; 
 TYPE_9__* dsl_dataset_phys (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 

int
dsl_dataset_get_holds(const char *dsname, nvlist_t *nvl)
{
	dsl_pool_t *dp;
	dsl_dataset_t *ds;
	int err;

	err = dsl_pool_hold(dsname, FTAG, &dp);
	if (err != 0)
		return (err);
	err = dsl_dataset_hold(dp, dsname, FTAG, &ds);
	if (err != 0) {
		dsl_pool_rele(dp, FTAG);
		return (err);
	}

	if (dsl_dataset_phys(ds)->ds_userrefs_obj != 0) {
		zap_attribute_t *za;
		zap_cursor_t zc;

		za = kmem_alloc(sizeof (zap_attribute_t), KM_SLEEP);
		for (zap_cursor_init(&zc, ds->ds_dir->dd_pool->dp_meta_objset,
		    dsl_dataset_phys(ds)->ds_userrefs_obj);
		    zap_cursor_retrieve(&zc, za) == 0;
		    zap_cursor_advance(&zc)) {
			fnvlist_add_uint64(nvl, za->za_name,
			    za->za_first_integer);
		}
		zap_cursor_fini(&zc);
		kmem_free(za, sizeof (zap_attribute_t));
	}
	dsl_dataset_rele(ds, FTAG);
	dsl_pool_rele(dp, FTAG);
	return (0);
}