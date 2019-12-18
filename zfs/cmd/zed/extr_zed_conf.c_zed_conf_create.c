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
struct zed_conf {int pid_fd; int state_fd; int zevent_fd; void* state_file; void* zedlet_dir; void* pid_file; void* conf_file; int /*<<< orphan*/ * zfs_hdl; int /*<<< orphan*/ * zedlets; int /*<<< orphan*/  max_events; int /*<<< orphan*/  min_events; int /*<<< orphan*/  syslog_facility; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  ZED_CONF_FILE ; 
 int /*<<< orphan*/  ZED_MAX_EVENTS ; 
 int /*<<< orphan*/  ZED_MIN_EVENTS ; 
 int /*<<< orphan*/  ZED_PID_FILE ; 
 int /*<<< orphan*/  ZED_STATE_FILE ; 
 int /*<<< orphan*/  ZED_ZEDLET_DIR ; 
 struct zed_conf* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_die (char*,int /*<<< orphan*/ ) ; 

struct zed_conf *
zed_conf_create(void)
{
	struct zed_conf *zcp;

	zcp = calloc(1, sizeof (*zcp));
	if (!zcp)
		goto nomem;

	zcp->syslog_facility = LOG_DAEMON;
	zcp->min_events = ZED_MIN_EVENTS;
	zcp->max_events = ZED_MAX_EVENTS;
	zcp->pid_fd = -1;
	zcp->zedlets = NULL;		/* created via zed_conf_scan_dir() */
	zcp->state_fd = -1;		/* opened via zed_conf_open_state() */
	zcp->zfs_hdl = NULL;		/* opened via zed_event_init() */
	zcp->zevent_fd = -1;		/* opened via zed_event_init() */

	if (!(zcp->conf_file = strdup(ZED_CONF_FILE)))
		goto nomem;

	if (!(zcp->pid_file = strdup(ZED_PID_FILE)))
		goto nomem;

	if (!(zcp->zedlet_dir = strdup(ZED_ZEDLET_DIR)))
		goto nomem;

	if (!(zcp->state_file = strdup(ZED_STATE_FILE)))
		goto nomem;

	return (zcp);

nomem:
	zed_log_die("Failed to create conf: %s", strerror(errno));
	return (NULL);
}