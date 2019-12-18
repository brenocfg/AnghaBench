#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_7__ {int /*<<< orphan*/  recv_nonce; int /*<<< orphan*/  shared_key; int /*<<< orphan*/  next_packet_length; int /*<<< orphan*/  sock; } ;
struct TYPE_6__ {TYPE_2__* accepted_connection_array; } ;
typedef  TYPE_1__ TCP_Server ;
typedef  TYPE_2__ TCP_Secure_Connection ;

/* Variables and functions */
 int MAX_PACKET_SIZE ; 
 int handle_TCP_packet (TYPE_1__*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kill_accepted (TYPE_1__*,size_t) ; 
 int read_packet_TCP_secure_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void do_confirmed_recv(TCP_Server *TCP_server, uint32_t i)
{
    TCP_Secure_Connection *conn = &TCP_server->accepted_connection_array[i];

    uint8_t packet[MAX_PACKET_SIZE];
    int len;

    while ((len = read_packet_TCP_secure_connection(conn->sock, &conn->next_packet_length, conn->shared_key,
                  conn->recv_nonce, packet, sizeof(packet)))) {
        if (len == -1) {
            kill_accepted(TCP_server, i);
            break;
        }

        if (handle_TCP_packet(TCP_server, i, packet, len) == -1) {
            kill_accepted(TCP_server, i);
            break;
        }
    }
}