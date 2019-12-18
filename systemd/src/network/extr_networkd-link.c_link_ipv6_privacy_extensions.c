#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; TYPE_1__* network; } ;
struct TYPE_5__ {int /*<<< orphan*/  ipv6_privacy_extensions; } ;
typedef  TYPE_2__ Link ;
typedef  int /*<<< orphan*/  IPv6PrivacyExtensions ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  _IPV6_PRIVACY_EXTENSIONS_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 

__attribute__((used)) static IPv6PrivacyExtensions link_ipv6_privacy_extensions(Link *link) {
        assert(link);

        if (!socket_ipv6_is_supported())
                return _IPV6_PRIVACY_EXTENSIONS_INVALID;

        if (link->flags & IFF_LOOPBACK)
                return _IPV6_PRIVACY_EXTENSIONS_INVALID;

        if (!link->network)
                return _IPV6_PRIVACY_EXTENSIONS_INVALID;

        return link->network->ipv6_privacy_extensions;
}