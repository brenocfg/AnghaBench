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
struct zed_conf {int state_fd; int pid_fd; int /*<<< orphan*/ * zedlets; struct zed_conf* state_file; struct zed_conf* zedlet_dir; struct zed_conf* pid_file; struct zed_conf* conf_file; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct zed_conf*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ unlink (struct zed_conf*) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,struct zed_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_strings_destroy (int /*<<< orphan*/ *) ; 

void
zed_conf_destroy(struct zed_conf *zcp)
{
	if (!zcp)
		return;

	if (zcp->state_fd >= 0) {
		if (close(zcp->state_fd) < 0)
			zed_log_msg(LOG_WARNING,
			    "Failed to close state file \"%s\": %s",
			    zcp->state_file, strerror(errno));
		zcp->state_fd = -1;
	}
	if (zcp->pid_file) {
		if ((unlink(zcp->pid_file) < 0) && (errno != ENOENT))
			zed_log_msg(LOG_WARNING,
			    "Failed to remove PID file \"%s\": %s",
			    zcp->pid_file, strerror(errno));
	}
	if (zcp->pid_fd >= 0) {
		if (close(zcp->pid_fd) < 0)
			zed_log_msg(LOG_WARNING,
			    "Failed to close PID file \"%s\": %s",
			    zcp->pid_file, strerror(errno));
		zcp->pid_fd = -1;
	}
	if (zcp->conf_file) {
		free(zcp->conf_file);
		zcp->conf_file = NULL;
	}
	if (zcp->pid_file) {
		free(zcp->pid_file);
		zcp->pid_file = NULL;
	}
	if (zcp->zedlet_dir) {
		free(zcp->zedlet_dir);
		zcp->zedlet_dir = NULL;
	}
	if (zcp->state_file) {
		free(zcp->state_file);
		zcp->state_file = NULL;
	}
	if (zcp->zedlets) {
		zed_strings_destroy(zcp->zedlets);
		zcp->zedlets = NULL;
	}
	free(zcp);
}