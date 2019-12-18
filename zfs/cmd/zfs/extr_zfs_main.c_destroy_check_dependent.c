#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {void* cb_dryrun; void* cb_error; void* cb_first; int /*<<< orphan*/ * cb_target; scalar_t__ cb_recurse; } ;
typedef  TYPE_1__ destroy_cbdata_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 char* zfs_type_to_name (scalar_t__) ; 

__attribute__((used)) static int
destroy_check_dependent(zfs_handle_t *zhp, void *data)
{
	destroy_cbdata_t *cbp = data;
	const char *tname = zfs_get_name(cbp->cb_target);
	const char *name = zfs_get_name(zhp);

	if (strncmp(tname, name, strlen(tname)) == 0 &&
	    (name[strlen(tname)] == '/' || name[strlen(tname)] == '@')) {
		/*
		 * This is a direct descendant, not a clone somewhere else in
		 * the hierarchy.
		 */
		if (cbp->cb_recurse)
			goto out;

		if (cbp->cb_first) {
			(void) fprintf(stderr, gettext("cannot destroy '%s': "
			    "%s has children\n"),
			    zfs_get_name(cbp->cb_target),
			    zfs_type_to_name(zfs_get_type(cbp->cb_target)));
			(void) fprintf(stderr, gettext("use '-r' to destroy "
			    "the following datasets:\n"));
			cbp->cb_first = B_FALSE;
			cbp->cb_error = B_TRUE;
		}

		(void) fprintf(stderr, "%s\n", zfs_get_name(zhp));
	} else {
		/*
		 * This is a clone.  We only want to report this if the '-r'
		 * wasn't specified, or the target is a snapshot.
		 */
		if (!cbp->cb_recurse &&
		    zfs_get_type(cbp->cb_target) != ZFS_TYPE_SNAPSHOT)
			goto out;

		if (cbp->cb_first) {
			(void) fprintf(stderr, gettext("cannot destroy '%s': "
			    "%s has dependent clones\n"),
			    zfs_get_name(cbp->cb_target),
			    zfs_type_to_name(zfs_get_type(cbp->cb_target)));
			(void) fprintf(stderr, gettext("use '-R' to destroy "
			    "the following datasets:\n"));
			cbp->cb_first = B_FALSE;
			cbp->cb_error = B_TRUE;
			cbp->cb_dryrun = B_TRUE;
		}

		(void) fprintf(stderr, "%s\n", zfs_get_name(zhp));
	}

out:
	zfs_close(zhp);
	return (0);
}