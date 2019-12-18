#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  zpool_prop_t ;
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_7__ {int za_integer_length; int /*<<< orphan*/  za_num_integers; int /*<<< orphan*/  za_name; int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {scalar_t__ spa_pool_props_object; int /*<<< orphan*/  spa_props_lock; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZPOOL_PROP_BOOTFS ; 
 int /*<<< orphan*/  ZPOOL_PROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_SRC_DEFAULT ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spa_get_dsl (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_prop_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_prop_get_config (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zpool_name_to_prop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_prop_default_numeric (int /*<<< orphan*/ ) ; 

int
spa_prop_get(spa_t *spa, nvlist_t **nvp)
{
	objset_t *mos = spa->spa_meta_objset;
	zap_cursor_t zc;
	zap_attribute_t za;
	int err;

	err = nvlist_alloc(nvp, NV_UNIQUE_NAME, KM_SLEEP);
	if (err)
		return (err);

	mutex_enter(&spa->spa_props_lock);

	/*
	 * Get properties from the spa config.
	 */
	spa_prop_get_config(spa, nvp);

	/* If no pool property object, no more prop to get. */
	if (mos == NULL || spa->spa_pool_props_object == 0) {
		mutex_exit(&spa->spa_props_lock);
		goto out;
	}

	/*
	 * Get properties from the MOS pool property object.
	 */
	for (zap_cursor_init(&zc, mos, spa->spa_pool_props_object);
	    (err = zap_cursor_retrieve(&zc, &za)) == 0;
	    zap_cursor_advance(&zc)) {
		uint64_t intval = 0;
		char *strval = NULL;
		zprop_source_t src = ZPROP_SRC_DEFAULT;
		zpool_prop_t prop;

		if ((prop = zpool_name_to_prop(za.za_name)) == ZPOOL_PROP_INVAL)
			continue;

		switch (za.za_integer_length) {
		case 8:
			/* integer property */
			if (za.za_first_integer !=
			    zpool_prop_default_numeric(prop))
				src = ZPROP_SRC_LOCAL;

			if (prop == ZPOOL_PROP_BOOTFS) {
				dsl_pool_t *dp;
				dsl_dataset_t *ds = NULL;

				dp = spa_get_dsl(spa);
				dsl_pool_config_enter(dp, FTAG);
				err = dsl_dataset_hold_obj(dp,
				    za.za_first_integer, FTAG, &ds);
				if (err != 0) {
					dsl_pool_config_exit(dp, FTAG);
					break;
				}

				strval = kmem_alloc(ZFS_MAX_DATASET_NAME_LEN,
				    KM_SLEEP);
				dsl_dataset_name(ds, strval);
				dsl_dataset_rele(ds, FTAG);
				dsl_pool_config_exit(dp, FTAG);
			} else {
				strval = NULL;
				intval = za.za_first_integer;
			}

			spa_prop_add_list(*nvp, prop, strval, intval, src);

			if (strval != NULL)
				kmem_free(strval, ZFS_MAX_DATASET_NAME_LEN);

			break;

		case 1:
			/* string property */
			strval = kmem_alloc(za.za_num_integers, KM_SLEEP);
			err = zap_lookup(mos, spa->spa_pool_props_object,
			    za.za_name, 1, za.za_num_integers, strval);
			if (err) {
				kmem_free(strval, za.za_num_integers);
				break;
			}
			spa_prop_add_list(*nvp, prop, strval, 0, src);
			kmem_free(strval, za.za_num_integers);
			break;

		default:
			break;
		}
	}
	zap_cursor_fini(&zc);
	mutex_exit(&spa->spa_props_lock);
out:
	if (err && err != ENOENT) {
		nvlist_free(*nvp);
		*nvp = NULL;
		return (err);
	}

	return (0);
}