#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nl_family; scalar_t__ nl_pid; } ;
union sockaddr_union {TYPE_1__ nl; } ;
struct ucred {scalar_t__ pid; } ;
struct sockaddr_nl {int dummy; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; scalar_t__ nlmsg_len; } ;
typedef  int socklen_t ;
typedef  void const Server ;

/* Variables and functions */
 scalar_t__ AF_NETLINK ; 
 size_t ALIGN (int) ; 
 scalar_t__ AUDIT_FIRST_USER_MSG ; 
 scalar_t__ AUDIT_USER ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLMSG_DATA (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  NLMSG_ERROR ; 
 int /*<<< orphan*/  NLMSG_NOOP ; 
 int /*<<< orphan*/  NLMSG_OK (struct nlmsghdr const*,size_t) ; 
 int /*<<< orphan*/  assert (void const*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  process_audit_string (void const*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void server_process_audit_message(
                Server *s,
                const void *buffer,
                size_t buffer_size,
                const struct ucred *ucred,
                const union sockaddr_union *sa,
                socklen_t salen) {

        const struct nlmsghdr *nl = buffer;

        assert(s);

        if (buffer_size < ALIGN(sizeof(struct nlmsghdr)))
                return;

        assert(buffer);

        /* Filter out fake data */
        if (!sa ||
            salen != sizeof(struct sockaddr_nl) ||
            sa->nl.nl_family != AF_NETLINK ||
            sa->nl.nl_pid != 0) {
                log_debug("Audit netlink message from invalid sender.");
                return;
        }

        if (!ucred || ucred->pid != 0) {
                log_debug("Audit netlink message with invalid credentials.");
                return;
        }

        if (!NLMSG_OK(nl, buffer_size)) {
                log_error("Audit netlink message truncated.");
                return;
        }

        /* Ignore special Netlink messages */
        if (IN_SET(nl->nlmsg_type, NLMSG_NOOP, NLMSG_ERROR))
                return;

        /* Except AUDIT_USER, all messages below AUDIT_FIRST_USER_MSG are control messages, let's ignore those */
        if (nl->nlmsg_type < AUDIT_FIRST_USER_MSG && nl->nlmsg_type != AUDIT_USER)
                return;

        process_audit_string(s, nl->nlmsg_type, NLMSG_DATA(nl), nl->nlmsg_len - ALIGN(sizeof(struct nlmsghdr)));
}