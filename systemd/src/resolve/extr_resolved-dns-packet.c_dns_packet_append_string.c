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
typedef  char const DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_packet_append_raw_string (char const*,char const*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int dns_packet_append_string(DnsPacket *p, const char *s, size_t *start) {
        assert(p);
        assert(s);

        return dns_packet_append_raw_string(p, s, strlen(s), start);
}