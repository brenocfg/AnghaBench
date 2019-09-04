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
typedef  scalar_t__ rstatus_t ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 scalar_t__ close (int) ; 
 scalar_t__ dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int fork () ; 
 int /*<<< orphan*/  log_error (char*,int,...) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int setsid () ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rstatus_t
nc_daemonize(int dump_core)
{
    rstatus_t status;
    pid_t pid, sid;
    int fd;

    pid = fork();
    switch (pid) {
    case -1:
        log_error("fork() failed: %s", strerror(errno));
        return NC_ERROR;

    case 0:
        break;

    default:
        /* parent terminates */
        _exit(0);
    }

    /* 1st child continues and becomes the session leader */

    sid = setsid();
    if (sid < 0) {
        log_error("setsid() failed: %s", strerror(errno));
        return NC_ERROR;
    }

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        log_error("signal(SIGHUP, SIG_IGN) failed: %s", strerror(errno));
        return NC_ERROR;
    }

    pid = fork();
    switch (pid) {
    case -1:
        log_error("fork() failed: %s", strerror(errno));
        return NC_ERROR;

    case 0:
        break;

    default:
        /* 1st child terminates */
        _exit(0);
    }

    /* 2nd child continues */

    /* change working directory */
    if (dump_core == 0) {
        status = chdir("/");
        if (status < 0) {
            log_error("chdir(\"/\") failed: %s", strerror(errno));
            return NC_ERROR;
        }
    }

    /* clear file mode creation mask */
    umask(0);

    /* redirect stdin, stdout and stderr to "/dev/null" */

    fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        log_error("open(\"/dev/null\") failed: %s", strerror(errno));
        return NC_ERROR;
    }

    status = dup2(fd, STDIN_FILENO);
    if (status < 0) {
        log_error("dup2(%d, STDIN) failed: %s", fd, strerror(errno));
        close(fd);
        return NC_ERROR;
    }

    status = dup2(fd, STDOUT_FILENO);
    if (status < 0) {
        log_error("dup2(%d, STDOUT) failed: %s", fd, strerror(errno));
        close(fd);
        return NC_ERROR;
    }

    status = dup2(fd, STDERR_FILENO);
    if (status < 0) {
        log_error("dup2(%d, STDERR) failed: %s", fd, strerror(errno));
        close(fd);
        return NC_ERROR;
    }

    if (fd > STDERR_FILENO) {
        status = close(fd);
        if (status < 0) {
            log_error("close(%d) failed: %s", fd, strerror(errno));
            return NC_ERROR;
        }
    }

    return NC_OK;
}