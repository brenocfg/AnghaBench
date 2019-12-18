#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; TYPE_1__* network; } ;
struct TYPE_7__ {scalar_t__ ipv6_accept_ra; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  link_ipv6_forward_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  link_ipv6ll_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 

__attribute__((used)) static bool link_ipv6_accept_ra_enabled(Link *link) {
        assert(link);

        if (!socket_ipv6_is_supported())
                return false;

        if (link->flags & IFF_LOOPBACK)
                return false;

        if (!link->network)
                return false;

        if (!link_ipv6ll_enabled(link))
                return false;

        /* If unset use system default (enabled if local forwarding is disabled.
         * disabled if local forwarding is enabled).
         * If set, ignore or enforce RA independent of local forwarding state.
         */
        if (link->network->ipv6_accept_ra < 0)
                /* default to accept RA if ip_forward is disabled and ignore RA if ip_forward is enabled */
                return !link_ipv6_forward_enabled(link);
        else if (link->network->ipv6_accept_ra > 0)
                /* accept RA even if ip_forward is enabled */
                return true;
        else
                /* ignore RA */
                return false;
}