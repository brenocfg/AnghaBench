#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  ds_hexsl ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  bslabel_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  CR_SL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INGLOBALZONE (int /*<<< orphan*/ ) ; 
 int MAXNAMELEN ; 
 int PRIV_FILE_DOWNGRADE_SL ; 
 int PRIV_FILE_UPGRADE_SL ; 
 int PRIV_POLICY (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZFS_MLSLABEL_DEFAULT ; 
 int /*<<< orphan*/  ZFS_PROP_MLSLABEL ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int /*<<< orphan*/  blequal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ blstrictdom (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int dsl_prop_get (char const*,int /*<<< orphan*/ ,int,int,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_prop_get_integer (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hexstr_to_label (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_check_global_label (char const*,char*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_set_slabel_policy(const char *name, char *strval, cred_t *cr)
{
#ifdef HAVE_MLSLABEL
	char		ds_hexsl[MAXNAMELEN];
	bslabel_t	ds_sl, new_sl;
	boolean_t	new_default = FALSE;
	uint64_t	zoned;
	int		needed_priv = -1;
	int		error;

	/* First get the existing dataset label. */
	error = dsl_prop_get(name, zfs_prop_to_name(ZFS_PROP_MLSLABEL),
	    1, sizeof (ds_hexsl), &ds_hexsl, NULL);
	if (error != 0)
		return (SET_ERROR(EPERM));

	if (strcasecmp(strval, ZFS_MLSLABEL_DEFAULT) == 0)
		new_default = TRUE;

	/* The label must be translatable */
	if (!new_default && (hexstr_to_label(strval, &new_sl) != 0))
		return (SET_ERROR(EINVAL));

	/*
	 * In a non-global zone, disallow attempts to set a label that
	 * doesn't match that of the zone; otherwise no other checks
	 * are needed.
	 */
	if (!INGLOBALZONE(curproc)) {
		if (new_default || !blequal(&new_sl, CR_SL(CRED())))
			return (SET_ERROR(EPERM));
		return (0);
	}

	/*
	 * For global-zone datasets (i.e., those whose zoned property is
	 * "off", verify that the specified new label is valid for the
	 * global zone.
	 */
	if (dsl_prop_get_integer(name,
	    zfs_prop_to_name(ZFS_PROP_ZONED), &zoned, NULL))
		return (SET_ERROR(EPERM));
	if (!zoned) {
		if (zfs_check_global_label(name, strval) != 0)
			return (SET_ERROR(EPERM));
	}

	/*
	 * If the existing dataset label is nondefault, check if the
	 * dataset is mounted (label cannot be changed while mounted).
	 * Get the zfsvfs_t; if there isn't one, then the dataset isn't
	 * mounted (or isn't a dataset, doesn't exist, ...).
	 */
	if (strcasecmp(ds_hexsl, ZFS_MLSLABEL_DEFAULT) != 0) {
		objset_t *os;
		static char *setsl_tag = "setsl_tag";

		/*
		 * Try to own the dataset; abort if there is any error,
		 * (e.g., already mounted, in use, or other error).
		 */
		error = dmu_objset_own(name, DMU_OST_ZFS, B_TRUE, B_TRUE,
		    setsl_tag, &os);
		if (error != 0)
			return (SET_ERROR(EPERM));

		dmu_objset_disown(os, B_TRUE, setsl_tag);

		if (new_default) {
			needed_priv = PRIV_FILE_DOWNGRADE_SL;
			goto out_check;
		}

		if (hexstr_to_label(strval, &new_sl) != 0)
			return (SET_ERROR(EPERM));

		if (blstrictdom(&ds_sl, &new_sl))
			needed_priv = PRIV_FILE_DOWNGRADE_SL;
		else if (blstrictdom(&new_sl, &ds_sl))
			needed_priv = PRIV_FILE_UPGRADE_SL;
	} else {
		/* dataset currently has a default label */
		if (!new_default)
			needed_priv = PRIV_FILE_UPGRADE_SL;
	}

out_check:
	if (needed_priv != -1)
		return (PRIV_POLICY(cr, needed_priv, B_FALSE, EPERM, NULL));
	return (0);
#else
	return (SET_ERROR(ENOTSUP));
#endif /* HAVE_MLSLABEL */
}