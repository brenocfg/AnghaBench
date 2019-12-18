#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_7__ {int outputfd; int inputfd; int /*<<< orphan*/  dedup_hdl; } ;
typedef  TYPE_2__ dedup_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EZFS_PIPEFAILED ; 
 int /*<<< orphan*/  EZFS_THREADCREATEFAILED ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  cksummer ; 
 int /*<<< orphan*/  close (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_dedup_fd(zfs_handle_t *zhp, dedup_arg_t *dda, int fd, pthread_t *tid,
    int *outfd)
{
	int pipefd[2];
	char errbuf[1024];
	int err;
	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "warning: cannot send '%s'"), zhp->zfs_name);
	if ((err = socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd)) != 0) {
		zfs_error_aux(zhp->zfs_hdl, strerror(errno));
		return (zfs_error(zhp->zfs_hdl, EZFS_PIPEFAILED,
		    errbuf));
	}
	dda->outputfd = fd;
	dda->inputfd = pipefd[1];
	dda->dedup_hdl = zhp->zfs_hdl;
	if ((err = pthread_create(tid, NULL, cksummer, dda)) != 0) {
		(void) close(pipefd[0]);
		(void) close(pipefd[1]);
		zfs_error_aux(zhp->zfs_hdl, strerror(err));
		return (zfs_error(zhp->zfs_hdl, EZFS_THREADCREATEFAILED,
		    errbuf));
	}
	*outfd = pipefd[0];
	return (0);
}