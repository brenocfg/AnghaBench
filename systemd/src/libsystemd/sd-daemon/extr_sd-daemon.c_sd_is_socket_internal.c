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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  other_type ;
typedef  int /*<<< orphan*/  accepting ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ACCEPTCONN ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_return (int,int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int sd_is_socket_internal(int fd, int type, int listening) {
        struct stat st_fd;

        assert_return(fd >= 0, -EBADF);
        assert_return(type >= 0, -EINVAL);

        if (fstat(fd, &st_fd) < 0)
                return -errno;

        if (!S_ISSOCK(st_fd.st_mode))
                return 0;

        if (type != 0) {
                int other_type = 0;
                socklen_t l = sizeof(other_type);

                if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &other_type, &l) < 0)
                        return -errno;

                if (l != sizeof(other_type))
                        return -EINVAL;

                if (other_type != type)
                        return 0;
        }

        if (listening >= 0) {
                int accepting = 0;
                socklen_t l = sizeof(accepting);

                if (getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &accepting, &l) < 0)
                        return -errno;

                if (l != sizeof(accepting))
                        return -EINVAL;

                if (!accepting != !listening)
                        return 0;
        }

        return 1;
}