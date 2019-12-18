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
typedef  scalar_t__ uint64_t ;
struct zed_conf {int /*<<< orphan*/  state_file; int /*<<< orphan*/  state_fd; } ;
struct iovec {int iov_len; scalar_t__* iov_base; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  etime ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ readv (int /*<<< orphan*/ ,struct iovec*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int
zed_conf_read_state(struct zed_conf *zcp, uint64_t *eidp, int64_t etime[])
{
	ssize_t len;
	struct iovec iov[3];
	ssize_t n;

	if (!zcp || !eidp || !etime) {
		errno = EINVAL;
		zed_log_msg(LOG_ERR,
		    "Failed to read state file: %s", strerror(errno));
		return (-1);
	}
	if (lseek(zcp->state_fd, 0, SEEK_SET) == (off_t)-1) {
		zed_log_msg(LOG_WARNING,
		    "Failed to reposition state file offset: %s",
		    strerror(errno));
		return (-1);
	}
	len = 0;
	iov[0].iov_base = eidp;
	len += iov[0].iov_len = sizeof (*eidp);
	iov[1].iov_base = &etime[0];
	len += iov[1].iov_len = sizeof (etime[0]);
	iov[2].iov_base = &etime[1];
	len += iov[2].iov_len = sizeof (etime[1]);

	n = readv(zcp->state_fd, iov, 3);
	if (n == 0) {
		*eidp = 0;
	} else if (n < 0) {
		zed_log_msg(LOG_WARNING,
		    "Failed to read state file \"%s\": %s",
		    zcp->state_file, strerror(errno));
		return (-1);
	} else if (n != len) {
		errno = EIO;
		zed_log_msg(LOG_WARNING,
		    "Failed to read state file \"%s\": Read %d of %d bytes",
		    zcp->state_file, n, len);
		return (-1);
	}
	return (0);
}