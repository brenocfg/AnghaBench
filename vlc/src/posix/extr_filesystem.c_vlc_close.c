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

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 int close (int) ; 
 scalar_t__ errno ; 
 int posix_close (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int vlc_close (int fd)
{
    int ret;
#ifdef POSIX_CLOSE_RESTART
    ret = posix_close(fd, 0);
#else
    ret = close(fd);
    /* POSIX.2008 (and earlier) does not specify if the file descriptor is
     * closed on failure. Assume it is as on Linux and most other common OSes.
     * Also emulate the correct error code as per newer POSIX versions. */
    if (unlikely(ret != 0) && unlikely(errno == EINTR))
        errno = EINPROGRESS;
#endif
    assert(ret == 0 || errno != EBADF); /* something is corrupt? */
    return ret;
}