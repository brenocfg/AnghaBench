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
struct TYPE_4__ {scalar_t__ max_size; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 size_t DNS_PACKET_SIZE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static inline size_t dns_packet_size_max(DnsPacket *p) {
        assert(p);

        /* Why not insist on a fully initialized max_size during DnsPacket construction? Well, this way it's easy to
         * allocate a transient, throw-away DnsPacket on the stack by simple zero initialization, without having to
         * deal with explicit field initialization. */

        return p->max_size != 0 ? p->max_size : DNS_PACKET_SIZE_MAX;
}