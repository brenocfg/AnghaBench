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
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_3__ {scalar_t__ cb_numattempted; scalar_t__ cb_numfailed; void* cb_noop; void* cb_recursive; int /*<<< orphan*/ * cb_keylocation; void* cb_loadkey; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ loadkey_cbdata_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int ZFS_ITER_RECURSE ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  load_key_callback ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usage (void*) ; 
 int zfs_for_each (int,char**,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
load_unload_keys(int argc, char **argv, boolean_t loadkey)
{
	int c, ret = 0, flags = 0;
	boolean_t do_all = B_FALSE;
	loadkey_cbdata_t cb = { 0 };

	cb.cb_loadkey = loadkey;

	while ((c = getopt(argc, argv, "anrL:")) != -1) {
		/* noop and alternate keylocations only apply to zfs load-key */
		if (loadkey) {
			switch (c) {
			case 'n':
				cb.cb_noop = B_TRUE;
				continue;
			case 'L':
				cb.cb_keylocation = optarg;
				continue;
			default:
				break;
			}
		}

		switch (c) {
		case 'a':
			do_all = B_TRUE;
			cb.cb_recursive = B_TRUE;
			break;
		case 'r':
			flags |= ZFS_ITER_RECURSE;
			cb.cb_recursive = B_TRUE;
			break;
		default:
			(void) fprintf(stderr,
			    gettext("invalid option '%c'\n"), optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	if (!do_all && argc == 0) {
		(void) fprintf(stderr,
		    gettext("Missing dataset argument or -a option\n"));
		usage(B_FALSE);
	}

	if (do_all && argc != 0) {
		(void) fprintf(stderr,
		    gettext("Cannot specify dataset with -a option\n"));
		usage(B_FALSE);
	}

	if (cb.cb_recursive && cb.cb_keylocation != NULL &&
	    strcmp(cb.cb_keylocation, "prompt") != 0) {
		(void) fprintf(stderr, gettext("alternate keylocation may only "
		    "be 'prompt' with -r or -a\n"));
		usage(B_FALSE);
	}

	ret = zfs_for_each(argc, argv, flags,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, NULL, NULL, 0,
	    load_key_callback, &cb);

	if (cb.cb_noop || (cb.cb_recursive && cb.cb_numattempted != 0)) {
		(void) printf(gettext("%llu / %llu key(s) successfully %s\n"),
		    (u_longlong_t)(cb.cb_numattempted - cb.cb_numfailed),
		    (u_longlong_t)cb.cb_numattempted,
		    loadkey ? (cb.cb_noop ? "verified" : "loaded") :
		    "unloaded");
	}

	if (cb.cb_numfailed != 0)
		ret = -1;

	return (ret);
}