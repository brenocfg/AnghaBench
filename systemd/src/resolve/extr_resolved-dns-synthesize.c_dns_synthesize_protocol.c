#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  DnsProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  DNS_PROTOCOL_LLMNR ; 
 int /*<<< orphan*/  DNS_PROTOCOL_MDNS ; 
 int SD_RESOLVED_DNS ; 
 int SD_RESOLVED_LLMNR ; 
 int SD_RESOLVED_MDNS ; 

DnsProtocol dns_synthesize_protocol(uint64_t flags) {

        /* Similar as dns_synthesize_family() but does this for the
         * protocol. If resolving via DNS was requested, we claim it
         * was DNS. Similar, if nothing specific was
         * requested. However, if only resolving via LLMNR was
         * requested we return that. */

        if (flags & SD_RESOLVED_DNS)
                return DNS_PROTOCOL_DNS;
        if (flags & SD_RESOLVED_LLMNR)
                return DNS_PROTOCOL_LLMNR;
        if (flags & SD_RESOLVED_MDNS)
                return DNS_PROTOCOL_MDNS;

        return DNS_PROTOCOL_DNS;
}