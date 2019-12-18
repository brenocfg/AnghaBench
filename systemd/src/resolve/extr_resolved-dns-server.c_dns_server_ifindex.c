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
struct TYPE_6__ {scalar_t__ ifindex; TYPE_1__* link; } ;
struct TYPE_5__ {int ifindex; } ;
typedef  TYPE_2__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 

int dns_server_ifindex(const DnsServer *s) {
        assert(s);

        /* The link ifindex always takes precedence */
        if (s->link)
                return s->link->ifindex;

        if (s->ifindex > 0)
                return s->ifindex;

        return 0;
}