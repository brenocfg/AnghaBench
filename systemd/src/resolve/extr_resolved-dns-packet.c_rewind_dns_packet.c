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
struct TYPE_3__ {int /*<<< orphan*/  saved_rindex; scalar_t__ packet; } ;
typedef  TYPE_1__ DnsPacketRewinder ;

/* Variables and functions */
 int /*<<< orphan*/  dns_packet_rewind (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rewind_dns_packet(DnsPacketRewinder *rewinder) {
        if (rewinder->packet)
                dns_packet_rewind(rewinder->packet, rewinder->saved_rindex);
}