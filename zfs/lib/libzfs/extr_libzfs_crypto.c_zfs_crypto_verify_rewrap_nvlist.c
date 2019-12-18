#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_prop_t ;
struct TYPE_4__ {int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zfs_type; int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
#define  ZFS_PROP_KEYFORMAT 130 
#define  ZFS_PROP_KEYLOCATION 129 
#define  ZFS_PROP_PBKDF2_ITERS 128 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_name_to_prop (char const*) ; 
 int /*<<< orphan*/  zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zfs_crypto_verify_rewrap_nvlist(zfs_handle_t *zhp, nvlist_t *props,
    nvlist_t **props_out, char *errbuf)
{
	int ret;
	nvpair_t *elem = NULL;
	zfs_prop_t prop;
	nvlist_t *new_props = NULL;

	new_props = fnvlist_alloc();

	/*
	 * loop through all provided properties, we should only have
	 * keyformat, keylocation and pbkdf2iters. The actual validation of
	 * values is done by zfs_valid_proplist().
	 */
	while ((elem = nvlist_next_nvpair(props, elem)) != NULL) {
		const char *propname = nvpair_name(elem);
		prop = zfs_name_to_prop(propname);

		switch (prop) {
		case ZFS_PROP_PBKDF2_ITERS:
		case ZFS_PROP_KEYFORMAT:
		case ZFS_PROP_KEYLOCATION:
			break;
		default:
			ret = EINVAL;
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "Only keyformat, keylocation and pbkdf2iters may "
			    "be set with this command."));
			goto error;
		}
	}

	new_props = zfs_valid_proplist(zhp->zfs_hdl, zhp->zfs_type, props,
	    zfs_prop_get_int(zhp, ZFS_PROP_ZONED), NULL, zhp->zpool_hdl,
	    B_TRUE, errbuf);
	if (new_props == NULL) {
		ret = EINVAL;
		goto error;
	}

	*props_out = new_props;
	return (0);

error:
	nvlist_free(new_props);
	*props_out = NULL;
	return (ret);
}