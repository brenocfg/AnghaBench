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
struct TYPE_3__ {int /*<<< orphan*/  link; int /*<<< orphan*/  fd; int /*<<< orphan*/  ip_service_type; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ sd_dhcp_client ;
typedef  int /*<<< orphan*/  DHCPPacket ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_PORT_SERVER ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_BROADCAST ; 
 int dhcp_network_send_raw_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dhcp_packet_append_ip_headers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dhcp_client_send_raw(
                sd_dhcp_client *client,
                DHCPPacket *packet,
                size_t len) {

        dhcp_packet_append_ip_headers(packet, INADDR_ANY, client->port,
                                      INADDR_BROADCAST, DHCP_PORT_SERVER, len, client->ip_service_type);

        return dhcp_network_send_raw_socket(client->fd, &client->link,
                                            packet, len);
}