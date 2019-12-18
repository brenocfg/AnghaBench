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
struct TYPE_3__ {int* last_packet; int last_packet_length; scalar_t__ last_packet_sent; } ;
typedef  TYPE_1__ TCP_Client_Connection ;

/* Variables and functions */

__attribute__((used)) static void proxy_socks5_generate_handshake(TCP_Client_Connection *TCP_conn)
{
    TCP_conn->last_packet[0] = 5; /* SOCKSv5 */
    TCP_conn->last_packet[1] = 1; /* number of authentication methods supported */
    TCP_conn->last_packet[2] = 0; /* No authentication */

    TCP_conn->last_packet_length = 3;
    TCP_conn->last_packet_sent = 0;
}