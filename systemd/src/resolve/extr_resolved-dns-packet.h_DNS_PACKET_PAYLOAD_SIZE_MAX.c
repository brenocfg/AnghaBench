#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {scalar_t__ ipproto; TYPE_2__* opt; } ;
struct TYPE_6__ {TYPE_1__* key; } ;
struct TYPE_5__ {int /*<<< orphan*/  class; } ;
typedef  TYPE_3__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_PACKET_SIZE_MAX ; 
 int /*<<< orphan*/  DNS_PACKET_UNICAST_SIZE_MAX ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t DNS_PACKET_PAYLOAD_SIZE_MAX(DnsPacket *p) {

        /* Returns the advertised maximum size for replies, or the DNS default if there's nothing defined. */

        if (p->ipproto == IPPROTO_TCP) /* we ignore EDNS(0) size data on TCP, like everybody else */
                return DNS_PACKET_SIZE_MAX;

        if (p->opt)
                return MAX(DNS_PACKET_UNICAST_SIZE_MAX, p->opt->key->class);

        return DNS_PACKET_UNICAST_SIZE_MAX;
}