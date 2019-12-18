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
struct msghdr {int /*<<< orphan*/  msg_iovlen; struct iovec* msg_iov; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  ELEMENTSOF (struct iovec*) ; 
 struct iovec IOVEC_MAKE_STRING (char const*) ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int errno ; 
 scalar_t__ journal_fd ; 
 int /*<<< orphan*/  log_do_header (char*,int,int,int,char const*,int,char const*,char const*,char const*,char const*,char const*) ; 
 scalar_t__ sendmsg (scalar_t__,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_to_journal(
                int level,
                int error,
                const char *file,
                int line,
                const char *func,
                const char *object_field,
                const char *object,
                const char *extra_field,
                const char *extra,
                const char *buffer) {

        char header[LINE_MAX];
        struct iovec iovec[4] = {};
        struct msghdr mh = {};

        if (journal_fd < 0)
                return 0;

        log_do_header(header, sizeof(header), level, error, file, line, func, object_field, object, extra_field, extra);

        iovec[0] = IOVEC_MAKE_STRING(header);
        iovec[1] = IOVEC_MAKE_STRING("MESSAGE=");
        iovec[2] = IOVEC_MAKE_STRING(buffer);
        iovec[3] = IOVEC_MAKE_STRING("\n");

        mh.msg_iov = iovec;
        mh.msg_iovlen = ELEMENTSOF(iovec);

        if (sendmsg(journal_fd, &mh, MSG_NOSIGNAL) < 0)
                return -errno;

        return 1;
}