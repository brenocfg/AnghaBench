#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {char const* cb_snapname; int /*<<< orphan*/  cb_max_taglen; int /*<<< orphan*/  cb_max_namelen; int /*<<< orphan*/ ** cb_nvlp; scalar_t__ cb_recursive; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ holds_cbdata_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int ZFS_ITER_RECURSE ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char const*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  holds_callback ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  print_holds (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int zfs_for_each (int,char**,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
zfs_do_holds(int argc, char **argv)
{
	int errors = 0;
	int c;
	int i;
	boolean_t scripted = B_FALSE;
	boolean_t recursive = B_FALSE;
	const char *opts = "rH";
	nvlist_t *nvl;

	int types = ZFS_TYPE_SNAPSHOT;
	holds_cbdata_t cb = { 0 };

	int limit = 0;
	int ret = 0;
	int flags = 0;

	/* check options */
	while ((c = getopt(argc, argv, opts)) != -1) {
		switch (c) {
		case 'r':
			recursive = B_TRUE;
			break;
		case 'H':
			scripted = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	if (recursive) {
		types |= ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME;
		flags |= ZFS_ITER_RECURSE;
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1)
		usage(B_FALSE);

	if (nvlist_alloc(&nvl, NV_UNIQUE_NAME, 0) != 0)
		nomem();

	for (i = 0; i < argc; ++i) {
		char *snapshot = argv[i];
		const char *delim;
		const char *snapname;

		delim = strchr(snapshot, '@');
		if (delim == NULL) {
			(void) fprintf(stderr,
			    gettext("'%s' is not a snapshot\n"), snapshot);
			++errors;
			continue;
		}
		snapname = delim + 1;
		if (recursive)
			snapshot[delim - snapshot] = '\0';

		cb.cb_recursive = recursive;
		cb.cb_snapname = snapname;
		cb.cb_nvlp = &nvl;

		/*
		 *  1. collect holds data, set format options
		 */
		ret = zfs_for_each(argc, argv, flags, types, NULL, NULL, limit,
		    holds_callback, &cb);
		if (ret != 0)
			++errors;
	}

	/*
	 *  2. print holds data
	 */
	print_holds(scripted, cb.cb_max_namelen, cb.cb_max_taglen, nvl);

	if (nvlist_empty(nvl))
		(void) fprintf(stderr, gettext("no datasets available\n"));

	nvlist_free(nvl);

	return (0 != errors);
}