#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_ndisc_router ;
typedef  int sd_ndisc_event ;
typedef  int /*<<< orphan*/  sd_ndisc ;
struct TYPE_6__ {int ndisc_configured; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
#define  SD_NDISC_EVENT_ROUTER 129 
#define  SD_NDISC_EVENT_TIMEOUT 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_check_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_warning (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ndisc_router_handler (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ndisc_handler(sd_ndisc *nd, sd_ndisc_event event, sd_ndisc_router *rt, void *userdata) {
        Link *link = userdata;

        assert(link);

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return;

        switch (event) {

        case SD_NDISC_EVENT_ROUTER:
                (void) ndisc_router_handler(link, rt);
                break;

        case SD_NDISC_EVENT_TIMEOUT:
                link->ndisc_configured = true;
                link_check_ready(link);

                break;
        default:
                log_link_warning(link, "IPv6 Neighbor Discovery unknown event: %d", event);
        }
}