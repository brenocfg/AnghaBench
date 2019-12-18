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

/* Variables and functions */
#define  DHCP_ACK 134 
#define  DHCP_DECLINE 133 
#define  DHCP_DISCOVER 132 
#define  DHCP_NAK 131 
#define  DHCP_OFFER 130 
#define  DHCP_RELEASE 129 
#define  DHCP_REQUEST 128 

__attribute__((used)) static const char *dhcp_type(int type) {
        switch(type) {
        case DHCP_DISCOVER:
                return "DHCPDISCOVER";
        case DHCP_OFFER:
                return "DHCPOFFER";
        case DHCP_REQUEST:
                return "DHCPREQUEST";
        case DHCP_DECLINE:
                return "DHCPDECLINE";
        case DHCP_ACK:
                return "DHCPACK";
        case DHCP_NAK:
                return "DHCPNAK";
        case DHCP_RELEASE:
                return "DHCPRELEASE";
        default:
                return "unknown";
        }
}