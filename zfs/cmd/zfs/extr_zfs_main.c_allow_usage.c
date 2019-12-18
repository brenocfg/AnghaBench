#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pd_visible; scalar_t__ pd_attr; char* pd_name; } ;
typedef  TYPE_1__ zprop_desc_t ;
typedef  int /*<<< orphan*/  zfs_deleg_note_t ;
typedef  int /*<<< orphan*/  opt_desc ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {char* z_perm; int /*<<< orphan*/  z_note; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  HELP_ALLOW ; 
 int /*<<< orphan*/  HELP_UNALLOW ; 
 scalar_t__ PROP_READONLY ; 
 int ZFS_NUM_DELEG_NOTES ; 
 int ZFS_NUM_PROPS ; 
 char* deleg_perm_comment (int /*<<< orphan*/ ) ; 
 char* deleg_perm_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,...) ; 
 char* get_usage (int /*<<< orphan*/ ) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  prop_cmp ; 
 int /*<<< orphan*/  qsort (char const**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 TYPE_3__* zfs_deleg_perm_tbl ; 
 TYPE_1__* zfs_prop_get_table () ; 

__attribute__((used)) static void
allow_usage(boolean_t un, boolean_t requested, const char *msg)
{
	const char *opt_desc[] = {
		"-h", gettext("show this help message and exit"),
		"-l", gettext("set permission locally"),
		"-d", gettext("set permission for descents"),
		"-u", gettext("set permission for user"),
		"-g", gettext("set permission for group"),
		"-e", gettext("set permission for everyone"),
		"-c", gettext("set create time permission"),
		"-s", gettext("define permission set"),
		/* unallow only */
		"-r", gettext("remove permissions recursively"),
	};
	size_t unallow_size = sizeof (opt_desc) / sizeof (char *);
	size_t allow_size = unallow_size - 2;
	const char *props[ZFS_NUM_PROPS];
	int i;
	size_t count = 0;
	FILE *fp = requested ? stdout : stderr;
	zprop_desc_t *pdtbl = zfs_prop_get_table();
	const char *fmt = gettext("%-16s %-14s\t%s\n");

	(void) fprintf(fp, gettext("Usage: %s\n"), get_usage(un ? HELP_UNALLOW :
	    HELP_ALLOW));
	(void) fprintf(fp, gettext("Options:\n"));
	for (i = 0; i < (un ? unallow_size : allow_size); i += 2) {
		const char *opt = opt_desc[i];
		const char *optdsc = opt_desc[i + 1];
		(void) fprintf(fp, gettext("  %-10s  %s\n"), opt, optdsc);
	}

	(void) fprintf(fp, gettext("\nThe following permissions are "
	    "supported:\n\n"));
	(void) fprintf(fp, fmt, gettext("NAME"), gettext("TYPE"),
	    gettext("NOTES"));
	for (i = 0; i < ZFS_NUM_DELEG_NOTES; i++) {
		const char *perm_name = zfs_deleg_perm_tbl[i].z_perm;
		zfs_deleg_note_t perm_note = zfs_deleg_perm_tbl[i].z_note;
		const char *perm_type = deleg_perm_type(perm_note);
		const char *perm_comment = deleg_perm_comment(perm_note);
		(void) fprintf(fp, fmt, perm_name, perm_type, perm_comment);
	}

	for (i = 0; i < ZFS_NUM_PROPS; i++) {
		zprop_desc_t *pd = &pdtbl[i];
		if (pd->pd_visible != B_TRUE)
			continue;

		if (pd->pd_attr == PROP_READONLY)
			continue;

		props[count++] = pd->pd_name;
	}
	props[count] = NULL;

	qsort(props, count, sizeof (char *), prop_cmp);

	for (i = 0; i < count; i++)
		(void) fprintf(fp, fmt, props[i], gettext("property"), "");

	if (msg != NULL)
		(void) fprintf(fp, gettext("\nzfs: error: %s"), msg);

	exit(requested ? 0 : 2);
}