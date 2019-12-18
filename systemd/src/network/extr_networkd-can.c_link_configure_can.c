#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  LINK_STATE_CONFIGURING ; 
 int link_down (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_down_handler ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int link_set_can (TYPE_1__*) ; 
 int /*<<< orphan*/  link_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int link_up_can (TYPE_1__*) ; 
 scalar_t__ streq_ptr (int /*<<< orphan*/ ,char*) ; 

int link_configure_can(Link *link) {
        int r;

        link_set_state(link, LINK_STATE_CONFIGURING);

        if (streq_ptr(link->kind, "can")) {
                /* The CAN interface must be down to configure bitrate, etc... */
                if ((link->flags & IFF_UP)) {
                        r = link_down(link, link_down_handler);
                        if (r < 0) {
                                link_enter_failed(link);
                                return r;
                        }
                } else {
                        r = link_set_can(link);
                        if (r < 0) {
                                link_enter_failed(link);
                                return r;
                        }
                }

                return 0;
        }

        if (!(link->flags & IFF_UP)) {
                r = link_up_can(link);
                if (r < 0) {
                        link_enter_failed(link);
                        return r;
                }
        }

        return 0;
}