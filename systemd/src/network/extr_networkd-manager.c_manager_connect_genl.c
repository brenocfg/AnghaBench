#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  event; int /*<<< orphan*/  genl; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  RCVBUF_SIZE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_genl_socket_open (int /*<<< orphan*/ *) ; 
 int sd_netlink_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_inc_rcvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int manager_connect_genl(Manager *m) {
        int r;

        assert(m);

        r = sd_genl_socket_open(&m->genl);
        if (r < 0)
                return r;

        r = sd_netlink_inc_rcvbuf(m->genl, RCVBUF_SIZE);
        if (r < 0)
                return r;

        r = sd_netlink_attach_event(m->genl, m->event, 0);
        if (r < 0)
                return r;

        return 0;
}