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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  vdev_aux_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  VDEV_AUX_EXTERNAL ; 
 int /*<<< orphan*/  VDEV_AUX_EXTERNAL_PERSIST ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zpool_vdev_fault (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_vdev_offline (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ zpool_vdev_path_to_guid (int /*<<< orphan*/ *,char*) ; 

int
zpool_do_offline(int argc, char **argv)
{
	int c, i;
	char *poolname;
	zpool_handle_t *zhp;
	int ret = 0;
	boolean_t istmp = B_FALSE;
	boolean_t fault = B_FALSE;

	/* check options */
	while ((c = getopt(argc, argv, "ft")) != -1) {
		switch (c) {
		case 'f':
			fault = B_TRUE;
			break;
		case 't':
			istmp = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* get pool name and check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name\n"));
		usage(B_FALSE);
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing device name\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];

	if ((zhp = zpool_open(g_zfs, poolname)) == NULL)
		return (1);

	for (i = 1; i < argc; i++) {
		if (fault) {
			uint64_t guid = zpool_vdev_path_to_guid(zhp, argv[i]);
			vdev_aux_t aux;
			if (istmp == B_FALSE) {
				/* Force the fault to persist across imports */
				aux = VDEV_AUX_EXTERNAL_PERSIST;
			} else {
				aux = VDEV_AUX_EXTERNAL;
			}

			if (guid == 0 || zpool_vdev_fault(zhp, guid, aux) != 0)
				ret = 1;
		} else {
			if (zpool_vdev_offline(zhp, argv[i], istmp) != 0)
				ret = 1;
		}
	}

	zpool_close(zhp);

	return (ret);
}