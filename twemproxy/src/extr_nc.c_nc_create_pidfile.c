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
struct instance {int pidfile; int /*<<< orphan*/  pid_filename; int /*<<< orphan*/  pid; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_ERROR ; 
 int /*<<< orphan*/  NC_OK ; 
 int NC_UINTMAX_MAXLEN ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nc_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nc_write (int,char*,int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rstatus_t
nc_create_pidfile(struct instance *nci)
{
    char pid[NC_UINTMAX_MAXLEN];
    int fd, pid_len;
    ssize_t n;

    fd = open(nci->pid_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        log_error("opening pid file '%s' failed: %s", nci->pid_filename,
                  strerror(errno));
        return NC_ERROR;
    }
    nci->pidfile = 1;

    pid_len = nc_snprintf(pid, NC_UINTMAX_MAXLEN, "%d", nci->pid);

    n = nc_write(fd, pid, pid_len);
    if (n < 0) {
        log_error("write to pid file '%s' failed: %s", nci->pid_filename,
                  strerror(errno));
        return NC_ERROR;
    }

    close(fd);

    return NC_OK;
}