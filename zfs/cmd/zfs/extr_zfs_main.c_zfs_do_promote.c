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
typedef  int /*<<< orphan*/  zfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zfs_promote (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_do_promote(int argc, char **argv)
{
	zfs_handle_t *zhp;
	int ret = 0;

	/* check options */
	if (argc > 1 && argv[1][0] == '-') {
		(void) fprintf(stderr, gettext("invalid option '%c'\n"),
		    argv[1][1]);
		usage(B_FALSE);
	}

	/* check number of arguments */
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing clone filesystem"
		    " argument\n"));
		usage(B_FALSE);
	}
	if (argc > 2) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	zhp = zfs_open(g_zfs, argv[1], ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
	if (zhp == NULL)
		return (1);

	ret = (zfs_promote(zhp) != 0);


	zfs_close(zhp);
	return (ret);
}