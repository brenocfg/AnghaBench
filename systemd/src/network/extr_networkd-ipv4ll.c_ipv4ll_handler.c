#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_ipv4ll ;
struct TYPE_9__ {int /*<<< orphan*/  state; struct TYPE_9__* network; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
#define  SD_IPV4LL_EVENT_BIND 130 
#define  SD_IPV4LL_EVENT_CONFLICT 129 
#define  SD_IPV4LL_EVENT_STOP 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int ipv4ll_address_claimed (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ipv4ll_address_lost (TYPE_1__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  log_link_warning (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int sd_ipv4ll_restart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipv4ll_handler(sd_ipv4ll *ll, int event, void *userdata) {
        Link *link = userdata;
        int r;

        assert(link);
        assert(link->network);

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return;

        switch(event) {
                case SD_IPV4LL_EVENT_STOP:
                        r = ipv4ll_address_lost(link);
                        if (r < 0) {
                                link_enter_failed(link);
                                return;
                        }
                        break;
                case SD_IPV4LL_EVENT_CONFLICT:
                        r = ipv4ll_address_lost(link);
                        if (r < 0) {
                                link_enter_failed(link);
                                return;
                        }

                        r = sd_ipv4ll_restart(ll);
                        if (r < 0)
                                log_link_warning_errno(link, r, "Could not acquire IPv4 link-local address: %m");
                        break;
                case SD_IPV4LL_EVENT_BIND:
                        r = ipv4ll_address_claimed(ll, link);
                        if (r < 0) {
                                log_link_error(link, "Failed to configure ipv4ll address: %m");
                                link_enter_failed(link);
                                return;
                        }
                        break;
                default:
                        log_link_warning(link, "IPv4 link-local unknown event: %d", event);
                        break;
        }
}