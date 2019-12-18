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

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 int SD_RESOLVED_DNS ; 
 int SD_RESOLVED_LLMNR_IPV4 ; 
 int SD_RESOLVED_LLMNR_IPV6 ; 
 int SD_RESOLVED_MDNS_IPV4 ; 
 int SD_RESOLVED_MDNS_IPV6 ; 

int dns_synthesize_family(uint64_t flags) {

        /* Picks an address family depending on set flags. This is
         * purely for synthesized answers, where the family we return
         * for the reply should match what was requested in the
         * question, even though we are synthesizing the answer
         * here. */

        if (!(flags & SD_RESOLVED_DNS)) {
                if (flags & (SD_RESOLVED_LLMNR_IPV4|SD_RESOLVED_MDNS_IPV4))
                        return AF_INET;
                if (flags & (SD_RESOLVED_LLMNR_IPV6|SD_RESOLVED_MDNS_IPV6))
                        return AF_INET6;
        }

        return AF_UNSPEC;
}