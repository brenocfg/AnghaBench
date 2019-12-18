#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
struct TYPE_5__ {scalar_t__ pl_prop; char* pl_user_prop; scalar_t__ pl_all; struct TYPE_5__* pl_next; } ;
typedef  TYPE_1__ zprop_list_t ;
struct TYPE_6__ {int /*<<< orphan*/  cb_literal; TYPE_1__* cb_proplist; } ;
typedef  TYPE_2__ zprop_get_cbdata_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  source ;
typedef  int /*<<< orphan*/  rbuf ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_MAXPROPLEN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ ZFS_PROP_NAME ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_SOURCE_VAL_RECVD ; 
 int /*<<< orphan*/  ZPROP_SRC_INHERITED ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  ZPROP_SRC_RECEIVED ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ is_recvd_column (TYPE_2__*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_get_user_props (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,scalar_t__,char*,int,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_recvd (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_userquota (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_written (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 
 char* zfs_prop_to_name (scalar_t__) ; 
 scalar_t__ zfs_prop_userquota (char*) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_written (char*) ; 
 int /*<<< orphan*/  zprop_print_one_property (int /*<<< orphan*/ ,TYPE_2__*,char*,char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
get_callback(zfs_handle_t *zhp, void *data)
{
	char buf[ZFS_MAXPROPLEN];
	char rbuf[ZFS_MAXPROPLEN];
	zprop_source_t sourcetype;
	char source[ZFS_MAX_DATASET_NAME_LEN];
	zprop_get_cbdata_t *cbp = data;
	nvlist_t *user_props = zfs_get_user_props(zhp);
	zprop_list_t *pl = cbp->cb_proplist;
	nvlist_t *propval;
	char *strval;
	char *sourceval;
	boolean_t received = is_recvd_column(cbp);

	for (; pl != NULL; pl = pl->pl_next) {
		char *recvdval = NULL;
		/*
		 * Skip the special fake placeholder.  This will also skip over
		 * the name property when 'all' is specified.
		 */
		if (pl->pl_prop == ZFS_PROP_NAME &&
		    pl == cbp->cb_proplist)
			continue;

		if (pl->pl_prop != ZPROP_INVAL) {
			if (zfs_prop_get(zhp, pl->pl_prop, buf,
			    sizeof (buf), &sourcetype, source,
			    sizeof (source),
			    cbp->cb_literal) != 0) {
				if (pl->pl_all)
					continue;
				if (!zfs_prop_valid_for_type(pl->pl_prop,
				    ZFS_TYPE_DATASET, B_FALSE)) {
					(void) fprintf(stderr,
					    gettext("No such property '%s'\n"),
					    zfs_prop_to_name(pl->pl_prop));
					continue;
				}
				sourcetype = ZPROP_SRC_NONE;
				(void) strlcpy(buf, "-", sizeof (buf));
			}

			if (received && (zfs_prop_get_recvd(zhp,
			    zfs_prop_to_name(pl->pl_prop), rbuf, sizeof (rbuf),
			    cbp->cb_literal) == 0))
				recvdval = rbuf;

			zprop_print_one_property(zfs_get_name(zhp), cbp,
			    zfs_prop_to_name(pl->pl_prop),
			    buf, sourcetype, source, recvdval);
		} else if (zfs_prop_userquota(pl->pl_user_prop)) {
			sourcetype = ZPROP_SRC_LOCAL;

			if (zfs_prop_get_userquota(zhp, pl->pl_user_prop,
			    buf, sizeof (buf), cbp->cb_literal) != 0) {
				sourcetype = ZPROP_SRC_NONE;
				(void) strlcpy(buf, "-", sizeof (buf));
			}

			zprop_print_one_property(zfs_get_name(zhp), cbp,
			    pl->pl_user_prop, buf, sourcetype, source, NULL);
		} else if (zfs_prop_written(pl->pl_user_prop)) {
			sourcetype = ZPROP_SRC_LOCAL;

			if (zfs_prop_get_written(zhp, pl->pl_user_prop,
			    buf, sizeof (buf), cbp->cb_literal) != 0) {
				sourcetype = ZPROP_SRC_NONE;
				(void) strlcpy(buf, "-", sizeof (buf));
			}

			zprop_print_one_property(zfs_get_name(zhp), cbp,
			    pl->pl_user_prop, buf, sourcetype, source, NULL);
		} else {
			if (nvlist_lookup_nvlist(user_props,
			    pl->pl_user_prop, &propval) != 0) {
				if (pl->pl_all)
					continue;
				sourcetype = ZPROP_SRC_NONE;
				strval = "-";
			} else {
				verify(nvlist_lookup_string(propval,
				    ZPROP_VALUE, &strval) == 0);
				verify(nvlist_lookup_string(propval,
				    ZPROP_SOURCE, &sourceval) == 0);

				if (strcmp(sourceval,
				    zfs_get_name(zhp)) == 0) {
					sourcetype = ZPROP_SRC_LOCAL;
				} else if (strcmp(sourceval,
				    ZPROP_SOURCE_VAL_RECVD) == 0) {
					sourcetype = ZPROP_SRC_RECEIVED;
				} else {
					sourcetype = ZPROP_SRC_INHERITED;
					(void) strlcpy(source,
					    sourceval, sizeof (source));
				}
			}

			if (received && (zfs_prop_get_recvd(zhp,
			    pl->pl_user_prop, rbuf, sizeof (rbuf),
			    cbp->cb_literal) == 0))
				recvdval = rbuf;

			zprop_print_one_property(zfs_get_name(zhp), cbp,
			    pl->pl_user_prop, strval, sourcetype,
			    source, recvdval);
		}
	}

	return (0);
}