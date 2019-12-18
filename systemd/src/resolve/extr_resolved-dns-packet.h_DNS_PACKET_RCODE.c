#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_1__* opt; } ;
struct TYPE_6__ {int ttl; } ;
typedef  TYPE_2__ DnsPacket ;

/* Variables and functions */
 TYPE_4__* DNS_PACKET_HEADER (TYPE_2__*) ; 
 int be16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t DNS_PACKET_RCODE(DnsPacket *p) {
        uint16_t rcode;

        if (p->opt)
                rcode = (uint16_t) (p->opt->ttl >> 24);
        else
                rcode = 0;

        return rcode | (be16toh(DNS_PACKET_HEADER(p)->flags) & 0xF);
}