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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parseprop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_callback ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int zfs_for_each (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_do_set(int argc, char **argv)
{
	nvlist_t *props = NULL;
	int ds_start = -1; /* argv idx of first dataset arg */
	int ret = 0;
	int i;

	/* check for options */
	if (argc > 1 && argv[1][0] == '-') {
		(void) fprintf(stderr, gettext("invalid option '%c'\n"),
		    argv[1][1]);
		usage(B_FALSE);
	}

	/* check number of arguments */
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing arguments\n"));
		usage(B_FALSE);
	}
	if (argc < 3) {
		if (strchr(argv[1], '=') == NULL) {
			(void) fprintf(stderr, gettext("missing property=value "
			    "argument(s)\n"));
		} else {
			(void) fprintf(stderr, gettext("missing dataset "
			    "name(s)\n"));
		}
		usage(B_FALSE);
	}

	/* validate argument order:  prop=val args followed by dataset args */
	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '=') != NULL) {
			if (ds_start > 0) {
				/* out-of-order prop=val argument */
				(void) fprintf(stderr, gettext("invalid "
				    "argument order\n"));
				usage(B_FALSE);
			}
		} else if (ds_start < 0) {
			ds_start = i;
		}
	}
	if (ds_start < 0) {
		(void) fprintf(stderr, gettext("missing dataset name(s)\n"));
		usage(B_FALSE);
	}

	/* Populate a list of property settings */
	if (nvlist_alloc(&props, NV_UNIQUE_NAME, 0) != 0)
		nomem();
	for (i = 1; i < ds_start; i++) {
		if (!parseprop(props, argv[i])) {
			ret = -1;
			goto error;
		}
	}

	ret = zfs_for_each(argc - ds_start, argv + ds_start, 0,
	    ZFS_TYPE_DATASET, NULL, NULL, 0, set_callback, props);

error:
	nvlist_free(props);
	return (ret);
}