#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_4__ {int /*<<< orphan*/  ping_request_id; } ;
typedef  TYPE_1__ TCP_Client_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_PACKET_PING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int write_packet_TCP_secure_connection (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int send_ping_request(TCP_Client_Connection *con)
{
    if (!con->ping_request_id)
        return 1;

    uint8_t packet[1 + sizeof(uint64_t)];
    packet[0] = TCP_PACKET_PING;
    memcpy(packet + 1, &con->ping_request_id, sizeof(uint64_t));
    int ret;

    if ((ret = write_packet_TCP_secure_connection(con, packet, sizeof(packet), 1)) == 1) {
        con->ping_request_id = 0;
    }

    return ret;
}