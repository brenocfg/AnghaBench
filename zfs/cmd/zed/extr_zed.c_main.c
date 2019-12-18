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
typedef  int /*<<< orphan*/  uint64_t ;
struct zed_conf {int /*<<< orphan*/  do_foreground; int /*<<< orphan*/  do_force; scalar_t__ do_memlock; scalar_t__ do_verbose; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ STDERR_FILENO ; 
 int /*<<< orphan*/  ZFS_META_RELEASE ; 
 int /*<<< orphan*/  ZFS_META_VERSION ; 
 int /*<<< orphan*/  _finish_daemonize () ; 
 int /*<<< orphan*/  _got_exit ; 
 scalar_t__ _got_hup ; 
 int /*<<< orphan*/  _lock_memory () ; 
 int /*<<< orphan*/  _setup_sig_handlers () ; 
 int /*<<< orphan*/  _start_daemonize () ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 
 struct zed_conf* zed_conf_create () ; 
 int /*<<< orphan*/  zed_conf_destroy (struct zed_conf*) ; 
 scalar_t__ zed_conf_open_state (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_conf_parse_file (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_conf_parse_opts (struct zed_conf*,int,char**) ; 
 scalar_t__ zed_conf_read_state (struct zed_conf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zed_conf_scan_dir (struct zed_conf*) ; 
 scalar_t__ zed_conf_write_pid (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_event_fini (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_event_init (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_event_seek (struct zed_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zed_event_service (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_file_close_from (scalar_t__) ; 
 int /*<<< orphan*/  zed_log_die (char*) ; 
 int /*<<< orphan*/  zed_log_fini () ; 
 int /*<<< orphan*/  zed_log_init (char*) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zed_log_stderr_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_syslog_open (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct zed_conf *zcp;
	uint64_t saved_eid;
	int64_t saved_etime[2];

	zed_log_init(argv[0]);
	zed_log_stderr_open(LOG_NOTICE);
	zcp = zed_conf_create();
	zed_conf_parse_opts(zcp, argc, argv);
	if (zcp->do_verbose)
		zed_log_stderr_open(LOG_INFO);

	if (geteuid() != 0)
		zed_log_die("Must be run as root");

	zed_conf_parse_file(zcp);

	zed_file_close_from(STDERR_FILENO + 1);

	(void) umask(0);

	if (chdir("/") < 0)
		zed_log_die("Failed to change to root directory");

	if (zed_conf_scan_dir(zcp) < 0)
		exit(EXIT_FAILURE);

	if (!zcp->do_foreground) {
		_start_daemonize();
		zed_log_syslog_open(LOG_DAEMON);
	}
	_setup_sig_handlers();

	if (zcp->do_memlock)
		_lock_memory();

	if ((zed_conf_write_pid(zcp) < 0) && (!zcp->do_force))
		exit(EXIT_FAILURE);

	if (!zcp->do_foreground)
		_finish_daemonize();

	zed_log_msg(LOG_NOTICE,
	    "ZFS Event Daemon %s-%s (PID %d)",
	    ZFS_META_VERSION, ZFS_META_RELEASE, (int)getpid());

	if (zed_conf_open_state(zcp) < 0)
		exit(EXIT_FAILURE);

	if (zed_conf_read_state(zcp, &saved_eid, saved_etime) < 0)
		exit(EXIT_FAILURE);

	zed_event_init(zcp);
	zed_event_seek(zcp, saved_eid, saved_etime);

	while (!_got_exit) {
		if (_got_hup) {
			_got_hup = 0;
			(void) zed_conf_scan_dir(zcp);
		}
		zed_event_service(zcp);
	}
	zed_log_msg(LOG_NOTICE, "Exiting");
	zed_event_fini(zcp);
	zed_conf_destroy(zcp);
	zed_log_fini();
	exit(EXIT_SUCCESS);
}