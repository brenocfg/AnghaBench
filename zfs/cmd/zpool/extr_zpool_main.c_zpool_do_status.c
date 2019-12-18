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
struct TYPE_3__ {scalar_t__ cb_count; void* cb_allpools; void* cb_first; void* cb_explain; int /*<<< orphan*/ * vcdl; void* cb_print_status; void* cb_print_vdev_trim; void* cb_dedup_stats; void* cb_verbose; void* cb_print_slow_ios; int /*<<< orphan*/  cb_name_flags; void* cb_literal; void* cb_print_vdev_init; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ status_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ NODATE ; 
 int /*<<< orphan*/  VDEV_NAME_FOLLOW_LINKS ; 
 int /*<<< orphan*/  VDEV_NAME_GUID ; 
 int /*<<< orphan*/  VDEV_NAME_PATH ; 
 int /*<<< orphan*/ * all_pools_for_each_vdev_run (int,char**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int for_each_pool (int,char**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_vdev_cmd_data_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsleep (float) ; 
 int /*<<< orphan*/  get_interval_count (int*,char**,float*,unsigned long*) ; 
 int /*<<< orphan*/  get_timestamp_arg (char) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  libzfs_envvar_is_set (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 char optopt ; 
 int /*<<< orphan*/  print_timestamp (scalar_t__) ; 
 int /*<<< orphan*/  print_zpool_script_list (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  status_callback ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ timestamp_fmt ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int
zpool_do_status(int argc, char **argv)
{
	int c;
	int ret;
	float interval = 0;
	unsigned long count = 0;
	status_cbdata_t cb = { 0 };
	char *cmd = NULL;

	/* check options */
	while ((c = getopt(argc, argv, "c:igLpPsvxDtT:")) != -1) {
		switch (c) {
		case 'c':
			if (cmd != NULL) {
				fprintf(stderr,
				    gettext("Can't set -c flag twice\n"));
				exit(1);
			}

			if (getenv("ZPOOL_SCRIPTS_ENABLED") != NULL &&
			    !libzfs_envvar_is_set("ZPOOL_SCRIPTS_ENABLED")) {
				fprintf(stderr, gettext(
				    "Can't run -c, disabled by "
				    "ZPOOL_SCRIPTS_ENABLED.\n"));
				exit(1);
			}

			if ((getuid() <= 0 || geteuid() <= 0) &&
			    !libzfs_envvar_is_set("ZPOOL_SCRIPTS_AS_ROOT")) {
				fprintf(stderr, gettext(
				    "Can't run -c with root privileges "
				    "unless ZPOOL_SCRIPTS_AS_ROOT is set.\n"));
				exit(1);
			}
			cmd = optarg;
			break;
		case 'i':
			cb.cb_print_vdev_init = B_TRUE;
			break;
		case 'g':
			cb.cb_name_flags |= VDEV_NAME_GUID;
			break;
		case 'L':
			cb.cb_name_flags |= VDEV_NAME_FOLLOW_LINKS;
			break;
		case 'p':
			cb.cb_literal = B_TRUE;
			break;
		case 'P':
			cb.cb_name_flags |= VDEV_NAME_PATH;
			break;
		case 's':
			cb.cb_print_slow_ios = B_TRUE;
			break;
		case 'v':
			cb.cb_verbose = B_TRUE;
			break;
		case 'x':
			cb.cb_explain = B_TRUE;
			break;
		case 'D':
			cb.cb_dedup_stats = B_TRUE;
			break;
		case 't':
			cb.cb_print_vdev_trim = B_TRUE;
			break;
		case 'T':
			get_timestamp_arg(*optarg);
			break;
		case '?':
			if (optopt == 'c') {
				print_zpool_script_list("status");
				exit(0);
			} else {
				fprintf(stderr,
				    gettext("invalid option '%c'\n"), optopt);
			}
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	get_interval_count(&argc, argv, &interval, &count);

	if (argc == 0)
		cb.cb_allpools = B_TRUE;

	cb.cb_first = B_TRUE;
	cb.cb_print_status = B_TRUE;

	for (;;) {
		if (timestamp_fmt != NODATE)
			print_timestamp(timestamp_fmt);

		if (cmd != NULL)
			cb.vcdl = all_pools_for_each_vdev_run(argc, argv, cmd,
			    NULL, NULL, 0, 0);

		ret = for_each_pool(argc, argv, B_TRUE, NULL,
		    status_callback, &cb);

		if (cb.vcdl != NULL)
			free_vdev_cmd_data_list(cb.vcdl);

		if (argc == 0 && cb.cb_count == 0)
			(void) fprintf(stderr, gettext("no pools available\n"));
		else if (cb.cb_explain && cb.cb_first && cb.cb_allpools)
			(void) printf(gettext("all pools are healthy\n"));

		if (ret != 0)
			return (ret);

		if (interval == 0)
			break;

		if (count != 0 && --count == 0)
			break;

		(void) fsleep(interval);
	}

	return (0);
}