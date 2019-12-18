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
struct TYPE_7__ {int /*<<< orphan*/  line; int /*<<< orphan*/  filename; } ;
struct TYPE_6__ {scalar_t__ session_id; scalar_t__ peer_session_id; TYPE_2__* section; int /*<<< orphan*/  name; struct TYPE_6__* tunnel; } ;
typedef  int /*<<< orphan*/  NetDev ;
typedef  TYPE_1__ L2tpSession ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * NETDEV (TYPE_1__*) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_netdev_error_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ section_is_invalid (TYPE_2__*) ; 

__attribute__((used)) static int l2tp_session_verify(L2tpSession *session) {
        NetDev *netdev;

        assert(session);
        assert(session->tunnel);

        netdev = NETDEV(session->tunnel);

        if (section_is_invalid(session->section))
                return -EINVAL;

        if (!session->name)
                return log_netdev_error_errno(netdev, SYNTHETIC_ERRNO(EINVAL),
                                              "%s: L2TP session without name configured. "
                                              "Ignoring [L2TPSession] section from line %u",
                                              session->section->filename, session->section->line);

        if (session->session_id == 0 || session->peer_session_id == 0)
                return log_netdev_error_errno(netdev, SYNTHETIC_ERRNO(EINVAL),
                                              "%s: L2TP session without session IDs configured. "
                                              "Ignoring [L2TPSession] section from line %u",
                                              session->section->filename, session->section->line);

        return 0;
}