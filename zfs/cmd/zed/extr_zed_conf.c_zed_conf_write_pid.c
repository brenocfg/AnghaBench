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
struct zed_conf {char* pid_file; int pid_fd; } ;
typedef  char* pid_t ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENAMETOOLONG ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PATH_MAX ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IRWXU ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fdatasync (int) ; 
 scalar_t__ getpid () ; 
 scalar_t__ mkdirp (char*,int const) ; 
 int open (char*,int,int const) ; 
 int snprintf (char*,int,char*,int) ; 
 char* strerror (scalar_t__) ; 
 int strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int umask (int) ; 
 char* zed_file_is_locked (int) ; 
 int zed_file_lock (int) ; 
 int zed_file_write_n (int,char*,int) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char*,...) ; 

int
zed_conf_write_pid(struct zed_conf *zcp)
{
	const mode_t dirmode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
	const mode_t filemode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char buf[PATH_MAX];
	int n;
	char *p;
	mode_t mask;
	int rv;

	if (!zcp || !zcp->pid_file) {
		errno = EINVAL;
		zed_log_msg(LOG_ERR, "Failed to create PID file: %s",
		    strerror(errno));
		return (-1);
	}
	assert(zcp->pid_fd == -1);
	/*
	 * Create PID file directory if needed.
	 */
	n = strlcpy(buf, zcp->pid_file, sizeof (buf));
	if (n >= sizeof (buf)) {
		errno = ENAMETOOLONG;
		zed_log_msg(LOG_ERR, "Failed to create PID file: %s",
		    strerror(errno));
		goto err;
	}
	p = strrchr(buf, '/');
	if (p)
		*p = '\0';

	if ((mkdirp(buf, dirmode) < 0) && (errno != EEXIST)) {
		zed_log_msg(LOG_ERR, "Failed to create directory \"%s\": %s",
		    buf, strerror(errno));
		goto err;
	}
	/*
	 * Obtain PID file lock.
	 */
	mask = umask(0);
	umask(mask | 022);
	zcp->pid_fd = open(zcp->pid_file, (O_RDWR | O_CREAT), filemode);
	umask(mask);
	if (zcp->pid_fd < 0) {
		zed_log_msg(LOG_ERR, "Failed to open PID file \"%s\": %s",
		    zcp->pid_file, strerror(errno));
		goto err;
	}
	rv = zed_file_lock(zcp->pid_fd);
	if (rv < 0) {
		zed_log_msg(LOG_ERR, "Failed to lock PID file \"%s\": %s",
		    zcp->pid_file, strerror(errno));
		goto err;
	} else if (rv > 0) {
		pid_t pid = zed_file_is_locked(zcp->pid_fd);
		if (pid < 0) {
			zed_log_msg(LOG_ERR,
			    "Failed to test lock on PID file \"%s\"",
			    zcp->pid_file);
		} else if (pid > 0) {
			zed_log_msg(LOG_ERR,
			    "Found PID %d bound to PID file \"%s\"",
			    pid, zcp->pid_file);
		} else {
			zed_log_msg(LOG_ERR,
			    "Inconsistent lock state on PID file \"%s\"",
			    zcp->pid_file);
		}
		goto err;
	}
	/*
	 * Write PID file.
	 */
	n = snprintf(buf, sizeof (buf), "%d\n", (int)getpid());
	if ((n < 0) || (n >= sizeof (buf))) {
		errno = ERANGE;
		zed_log_msg(LOG_ERR, "Failed to write PID file \"%s\": %s",
		    zcp->pid_file, strerror(errno));
	} else if (zed_file_write_n(zcp->pid_fd, buf, n) != n) {
		zed_log_msg(LOG_ERR, "Failed to write PID file \"%s\": %s",
		    zcp->pid_file, strerror(errno));
	} else if (fdatasync(zcp->pid_fd) < 0) {
		zed_log_msg(LOG_ERR, "Failed to sync PID file \"%s\": %s",
		    zcp->pid_file, strerror(errno));
	} else {
		return (0);
	}

err:
	if (zcp->pid_fd >= 0) {
		(void) close(zcp->pid_fd);
		zcp->pid_fd = -1;
	}
	return (-1);
}