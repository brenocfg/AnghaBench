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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  TCP_Client_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_PACKET_DISCONNECT_NOTIFICATION ; 
 int write_packet_TCP_secure_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int send_disconnect_notification(TCP_Client_Connection *con, uint8_t id)
{
    uint8_t packet[1 + 1];
    packet[0] = TCP_PACKET_DISCONNECT_NOTIFICATION;
    packet[1] = id;
    return write_packet_TCP_secure_connection(con, packet, sizeof(packet), 1);
}