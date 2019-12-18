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
typedef  int /*<<< orphan*/  DnsPacket ;

/* Variables and functions */
 scalar_t__ DNS_PACKET_ANCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ DNS_PACKET_ARCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ DNS_PACKET_NSCOUNT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned DNS_PACKET_RRCOUNT(DnsPacket *p) {
        return
                (unsigned) DNS_PACKET_ANCOUNT(p) +
                (unsigned) DNS_PACKET_NSCOUNT(p) +
                (unsigned) DNS_PACKET_ARCOUNT(p);
}