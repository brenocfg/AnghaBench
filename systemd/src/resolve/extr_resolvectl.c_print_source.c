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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  rtt_str ;

/* Variables and functions */
 int FORMAT_TIMESTAMP_MAX ; 
 int SD_RESOLVED_AUTHENTICATED ; 
 int SD_RESOLVED_DNS ; 
 int SD_RESOLVED_LLMNR_IPV4 ; 
 int SD_RESOLVED_LLMNR_IPV6 ; 
 int SD_RESOLVED_MDNS_IPV4 ; 
 int SD_RESOLVED_MDNS_IPV6 ; 
 char* ansi_grey () ; 
 char* ansi_normal () ; 
 int /*<<< orphan*/  arg_legend ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_timespan (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* yes_no (int) ; 

__attribute__((used)) static void print_source(uint64_t flags, usec_t rtt) {
        char rtt_str[FORMAT_TIMESTAMP_MAX];

        if (!arg_legend)
                return;

        if (flags == 0)
                return;

        printf("\n%s-- Information acquired via", ansi_grey());

        if (flags != 0)
                printf(" protocol%s%s%s%s%s",
                       flags & SD_RESOLVED_DNS ? " DNS" :"",
                       flags & SD_RESOLVED_LLMNR_IPV4 ? " LLMNR/IPv4" : "",
                       flags & SD_RESOLVED_LLMNR_IPV6 ? " LLMNR/IPv6" : "",
                       flags & SD_RESOLVED_MDNS_IPV4 ? " mDNS/IPv4" : "",
                       flags & SD_RESOLVED_MDNS_IPV6 ? " mDNS/IPv6" : "");

        assert_se(format_timespan(rtt_str, sizeof(rtt_str), rtt, 100));

        printf(" in %s.%s\n"
               "%s-- Data is authenticated: %s%s\n",
               rtt_str, ansi_normal(),
               ansi_grey(), yes_no(flags & SD_RESOLVED_AUTHENTICATED), ansi_normal());
}