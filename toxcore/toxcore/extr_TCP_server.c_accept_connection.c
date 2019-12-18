#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  sock_t ;
struct TYPE_6__ {scalar_t__ status; scalar_t__ next_packet_length; int /*<<< orphan*/  sock; } ;
struct TYPE_5__ {size_t incomming_connection_queue_index; TYPE_2__* incomming_connection_queue; } ;
typedef  TYPE_1__ TCP_Server ;
typedef  TYPE_2__ TCP_Secure_Connection ;

/* Variables and functions */
 size_t MAX_INCOMMING_CONNECTIONS ; 
 scalar_t__ TCP_STATUS_CONNECTED ; 
 scalar_t__ TCP_STATUS_NO_STATUS ; 
 int /*<<< orphan*/  kill_TCP_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  kill_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_socket_nonblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_socket_nosigpipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int accept_connection(TCP_Server *TCP_server, sock_t sock)
{
    if (!sock_valid(sock))
        return -1;

    if (!set_socket_nonblock(sock)) {
        kill_sock(sock);
        return -1;
    }

    if (!set_socket_nosigpipe(sock)) {
        kill_sock(sock);
        return -1;
    }

    uint16_t index = TCP_server->incomming_connection_queue_index % MAX_INCOMMING_CONNECTIONS;

    TCP_Secure_Connection *conn = &TCP_server->incomming_connection_queue[index];

    if (conn->status != TCP_STATUS_NO_STATUS)
        kill_TCP_connection(conn);

    conn->status = TCP_STATUS_CONNECTED;
    conn->sock = sock;
    conn->next_packet_length = 0;

    ++TCP_server->incomming_connection_queue_index;
    return index;
}