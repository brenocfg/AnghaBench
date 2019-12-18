#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  opt; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int DNS_RESOURCE_RECORD_OPT_VERSION_SUPPORTED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool DNS_PACKET_VERSION_SUPPORTED(DnsPacket *p) {
        /* Returns true if this packet is in a version we support. Which means either non-EDNS or EDNS(0), but not EDNS
         * of any newer versions */

        if (!p->opt)
                return true;

        return DNS_RESOURCE_RECORD_OPT_VERSION_SUPPORTED(p->opt);
}