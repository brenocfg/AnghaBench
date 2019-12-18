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
typedef  int DnsProtocol ;

/* Variables and functions */
 int AF_INET6 ; 
#define  DNS_PROTOCOL_DNS 130 
#define  DNS_PROTOCOL_LLMNR 129 
#define  DNS_PROTOCOL_MDNS 128 
 int SD_RESOLVED_AUTHENTICATED ; 
 int SD_RESOLVED_DNS ; 
 int SD_RESOLVED_LLMNR_IPV4 ; 
 int SD_RESOLVED_LLMNR_IPV6 ; 
 int SD_RESOLVED_MDNS_IPV4 ; 
 int SD_RESOLVED_MDNS_IPV6 ; 

__attribute__((used)) static inline uint64_t SD_RESOLVED_FLAGS_MAKE(DnsProtocol protocol, int family, bool authenticated) {
        uint64_t f;

        /* Converts a protocol + family into a flags field as used in queries and responses */

        f = authenticated ? SD_RESOLVED_AUTHENTICATED : 0;

        switch (protocol) {
        case DNS_PROTOCOL_DNS:
                return f|SD_RESOLVED_DNS;

        case DNS_PROTOCOL_LLMNR:
                return f|(family == AF_INET6 ? SD_RESOLVED_LLMNR_IPV6 : SD_RESOLVED_LLMNR_IPV4);

        case DNS_PROTOCOL_MDNS:
                return f|(family == AF_INET6 ? SD_RESOLVED_MDNS_IPV6 : SD_RESOLVED_MDNS_IPV4);

        default:
                return f;
        }
}