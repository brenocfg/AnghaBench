#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_7__ {struct TYPE_7__* dd_parent; TYPE_3__* dd_pool; } ;
typedef  TYPE_1__ dsl_dir_t ;
typedef  int boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  dd_props_zapobj; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int ENOENT ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZPROP_INHERIT_SUFFIX ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_RECVD_SUFFIX ; 
 int /*<<< orphan*/  ZPROP_SOURCE_VAL_RECVD ; 
 int dodefault (scalar_t__,int,int,void*) ; 
 int /*<<< orphan*/  dsl_dir_name (TYPE_1__*,char*) ; 
 TYPE_4__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (TYPE_3__*) ; 
 char* kmem_asprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int zap_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,void*) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_inheritable (scalar_t__) ; 

int
dsl_prop_get_dd(dsl_dir_t *dd, const char *propname,
    int intsz, int numints, void *buf, char *setpoint, boolean_t snapshot)
{
	int err = ENOENT;
	dsl_dir_t *target = dd;
	objset_t *mos = dd->dd_pool->dp_meta_objset;
	zfs_prop_t prop;
	boolean_t inheritable;
	boolean_t inheriting = B_FALSE;
	char *inheritstr;
	char *recvdstr;

	ASSERT(dsl_pool_config_held(dd->dd_pool));

	if (setpoint)
		setpoint[0] = '\0';

	prop = zfs_name_to_prop(propname);
	inheritable = (prop == ZPROP_INVAL || zfs_prop_inheritable(prop));
	inheritstr = kmem_asprintf("%s%s", propname, ZPROP_INHERIT_SUFFIX);
	recvdstr = kmem_asprintf("%s%s", propname, ZPROP_RECVD_SUFFIX);

	/*
	 * Note: dd may become NULL, therefore we shouldn't dereference it
	 * after this loop.
	 */
	for (; dd != NULL; dd = dd->dd_parent) {
		if (dd != target || snapshot) {
			if (!inheritable)
				break;
			inheriting = B_TRUE;
		}

		/* Check for a local value. */
		err = zap_lookup(mos, dsl_dir_phys(dd)->dd_props_zapobj,
		    propname, intsz, numints, buf);
		if (err != ENOENT) {
			if (setpoint != NULL && err == 0)
				dsl_dir_name(dd, setpoint);
			break;
		}

		/*
		 * Skip the check for a received value if there is an explicit
		 * inheritance entry.
		 */
		err = zap_contains(mos, dsl_dir_phys(dd)->dd_props_zapobj,
		    inheritstr);
		if (err != 0 && err != ENOENT)
			break;

		if (err == ENOENT) {
			/* Check for a received value. */
			err = zap_lookup(mos, dsl_dir_phys(dd)->dd_props_zapobj,
			    recvdstr, intsz, numints, buf);
			if (err != ENOENT) {
				if (setpoint != NULL && err == 0) {
					if (inheriting) {
						dsl_dir_name(dd, setpoint);
					} else {
						(void) strcpy(setpoint,
						    ZPROP_SOURCE_VAL_RECVD);
					}
				}
				break;
			}
		}

		/*
		 * If we found an explicit inheritance entry, err is zero even
		 * though we haven't yet found the value, so reinitializing err
		 * at the end of the loop (instead of at the beginning) ensures
		 * that err has a valid post-loop value.
		 */
		err = SET_ERROR(ENOENT);
	}

	if (err == ENOENT)
		err = dodefault(prop, intsz, numints, buf);

	kmem_strfree(inheritstr);
	kmem_strfree(recvdstr);

	return (err);
}