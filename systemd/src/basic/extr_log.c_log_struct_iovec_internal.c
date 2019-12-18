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
struct msghdr {int msg_iovlen; struct iovec* msg_iov; } ;
struct iovec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  header ;
typedef  size_t LogRealm ;

/* Variables and functions */
 int ERRNO_VALUE (int) ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iovec IOVEC_MAKE_STRING (char*) ; 
 int LINE_MAX ; 
 int LOG_FACMASK ; 
 scalar_t__ LOG_PRI (int) ; 
 size_t LOG_REALM_REMOVE_LEVEL (int) ; 
 int /*<<< orphan*/  LOG_TARGET_AUTO ; 
 int /*<<< orphan*/  LOG_TARGET_JOURNAL ; 
 int /*<<< orphan*/  LOG_TARGET_JOURNAL_OR_KMSG ; 
 scalar_t__ LOG_TARGET_NULL ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  PROTECT_ERRNO ; 
 scalar_t__ STRLEN (char*) ; 
 scalar_t__ _likely_ (int) ; 
 scalar_t__ _unlikely_ (int) ; 
 scalar_t__ journal_fd ; 
 int log_dispatch_internal (int,int,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_do_header (char*,int,int,int,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int log_facility ; 
 scalar_t__* log_max_level ; 
 scalar_t__ log_target ; 
 scalar_t__ memory_startswith (scalar_t__,scalar_t__,char*) ; 
 scalar_t__ sendmsg (scalar_t__,struct msghdr*,int /*<<< orphan*/ ) ; 
 char* strndupa (scalar_t__,scalar_t__) ; 

int log_struct_iovec_internal(
                int level,
                int error,
                const char *file,
                int line,
                const char *func,
                const struct iovec input_iovec[],
                size_t n_input_iovec) {

        LogRealm realm = LOG_REALM_REMOVE_LEVEL(level);
        PROTECT_ERRNO;
        size_t i;
        char *m;

        if (_likely_(LOG_PRI(level) > log_max_level[realm]) ||
            log_target == LOG_TARGET_NULL)
                return -ERRNO_VALUE(error);

        if ((level & LOG_FACMASK) == 0)
                level |= log_facility;

        if (IN_SET(log_target, LOG_TARGET_AUTO,
                               LOG_TARGET_JOURNAL_OR_KMSG,
                               LOG_TARGET_JOURNAL) &&
            journal_fd >= 0) {

                struct iovec iovec[1 + n_input_iovec*2];
                char header[LINE_MAX];
                struct msghdr mh = {
                        .msg_iov = iovec,
                        .msg_iovlen = 1 + n_input_iovec*2,
                };

                log_do_header(header, sizeof(header), level, error, file, line, func, NULL, NULL, NULL, NULL);
                iovec[0] = IOVEC_MAKE_STRING(header);

                for (i = 0; i < n_input_iovec; i++) {
                        iovec[1+i*2] = input_iovec[i];
                        iovec[1+i*2+1] = IOVEC_MAKE_STRING("\n");
                }

                if (sendmsg(journal_fd, &mh, MSG_NOSIGNAL) >= 0)
                        return -ERRNO_VALUE(error);
        }

        for (i = 0; i < n_input_iovec; i++)
                if (memory_startswith(input_iovec[i].iov_base, input_iovec[i].iov_len, "MESSAGE="))
                        break;

        if (_unlikely_(i >= n_input_iovec)) /* Couldn't find MESSAGE=? */
                return -ERRNO_VALUE(error);

        m = strndupa(input_iovec[i].iov_base + STRLEN("MESSAGE="),
                     input_iovec[i].iov_len - STRLEN("MESSAGE="));

        return log_dispatch_internal(level, error, file, line, func, NULL, NULL, NULL, NULL, m);
}