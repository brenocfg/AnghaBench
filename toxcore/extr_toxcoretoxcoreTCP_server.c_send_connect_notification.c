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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  TCP_Secure_Connection ;

/* Variables and functions */
 scalar_t__ NUM_RESERVED_PORTS ; 
 scalar_t__ TCP_PACKET_CONNECTION_NOTIFICATION ; 
 int write_packet_TCP_secure_connection (int /*<<< orphan*/ *,scalar_t__*,int,int) ; 

__attribute__((used)) static int send_connect_notification(TCP_Secure_Connection *con, uint8_t id)
{
    uint8_t data[2] = {TCP_PACKET_CONNECTION_NOTIFICATION, id + NUM_RESERVED_PORTS};
    return write_packet_TCP_secure_connection(con, data, sizeof(data), 1);
}