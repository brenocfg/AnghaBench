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
struct TYPE_8__ {int /*<<< orphan*/  claimed_address; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ sd_ipv4ll ;
typedef  TYPE_1__ sd_ipv4acd ;

/* Variables and functions */
 int /*<<< orphan*/  IPV4LL_DONT_DESTROY (TYPE_1__*) ; 
#define  SD_IPV4ACD_EVENT_BIND 130 
#define  SD_IPV4ACD_EVENT_CONFLICT 129 
#define  SD_IPV4ACD_EVENT_STOP 128 
 int /*<<< orphan*/  SD_IPV4LL_EVENT_BIND ; 
 int /*<<< orphan*/  SD_IPV4LL_EVENT_CONFLICT ; 
 int /*<<< orphan*/  SD_IPV4LL_EVENT_STOP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  ipv4ll_client_notify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sd_ipv4ll_restart (TYPE_1__*) ; 

void ipv4ll_on_acd(sd_ipv4acd *acd, int event, void *userdata) {
        sd_ipv4ll *ll = userdata;
        IPV4LL_DONT_DESTROY(ll);
        int r;

        assert(acd);
        assert(ll);

        switch (event) {

        case SD_IPV4ACD_EVENT_STOP:
                ipv4ll_client_notify(ll, SD_IPV4LL_EVENT_STOP);
                ll->claimed_address = 0;
                break;

        case SD_IPV4ACD_EVENT_BIND:
                ll->claimed_address = ll->address;
                ipv4ll_client_notify(ll, SD_IPV4LL_EVENT_BIND);
                break;

        case SD_IPV4ACD_EVENT_CONFLICT:
                /* if an address was already bound we must call up to the
                   user to handle this, otherwise we just try again */
                if (ll->claimed_address != 0) {
                        ipv4ll_client_notify(ll, SD_IPV4LL_EVENT_CONFLICT);

                        ll->claimed_address = 0;
                } else {
                        r = sd_ipv4ll_restart(ll);
                        if (r < 0)
                                goto error;
                }

                break;

        default:
                assert_not_reached("Invalid IPv4ACD event.");
        }

        return;

error:
        ipv4ll_client_notify(ll, SD_IPV4LL_EVENT_STOP);
}