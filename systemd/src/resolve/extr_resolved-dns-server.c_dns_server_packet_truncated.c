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
struct TYPE_4__ {scalar_t__ possible_feature_level; int packet_truncated; } ;
typedef  scalar_t__ DnsServerFeatureLevel ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void dns_server_packet_truncated(DnsServer *s, DnsServerFeatureLevel level) {
        assert(s);

        /* Invoked whenever we get a packet with TC bit set. */

        if (s->possible_feature_level != level)
                return;

        s->packet_truncated = true;
}