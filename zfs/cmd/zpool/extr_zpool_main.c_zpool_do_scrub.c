#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cb_type; scalar_t__ cb_scrub_cmd; } ;
typedef  TYPE_1__ zpool_wait_activity_t ;
typedef  TYPE_1__ scrub_cbdata_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ POOL_SCAN_NONE ; 
 scalar_t__ POOL_SCAN_SCRUB ; 
 scalar_t__ POOL_SCRUB_NORMAL ; 
 scalar_t__ POOL_SCRUB_PAUSE ; 
 TYPE_1__ ZPOOL_WAIT_SCRUB ; 
 int for_each_pool (int,char**,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  scrub_callback ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  wait_callback ; 

int
zpool_do_scrub(int argc, char **argv)
{
	int c;
	scrub_cbdata_t cb;
	boolean_t wait = B_FALSE;
	int error;

	cb.cb_type = POOL_SCAN_SCRUB;
	cb.cb_scrub_cmd = POOL_SCRUB_NORMAL;

	/* check options */
	while ((c = getopt(argc, argv, "spw")) != -1) {
		switch (c) {
		case 's':
			cb.cb_type = POOL_SCAN_NONE;
			break;
		case 'p':
			cb.cb_scrub_cmd = POOL_SCRUB_PAUSE;
			break;
		case 'w':
			wait = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	if (cb.cb_type == POOL_SCAN_NONE &&
	    cb.cb_scrub_cmd == POOL_SCRUB_PAUSE) {
		(void) fprintf(stderr, gettext("invalid option combination: "
		    "-s and -p are mutually exclusive\n"));
		usage(B_FALSE);
	}

	if (wait && (cb.cb_type == POOL_SCAN_NONE ||
	    cb.cb_scrub_cmd == POOL_SCRUB_PAUSE)) {
		(void) fprintf(stderr, gettext("invalid option combination: "
		    "-w cannot be used with -p or -s\n"));
		usage(B_FALSE);
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name argument\n"));
		usage(B_FALSE);
	}

	error = for_each_pool(argc, argv, B_TRUE, NULL, scrub_callback, &cb);

	if (wait && !error) {
		zpool_wait_activity_t act = ZPOOL_WAIT_SCRUB;
		error = for_each_pool(argc, argv, B_TRUE, NULL, wait_callback,
		    &act);
	}

	return (error);
}