#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_9__ {int unconfirmed_connection_queue_index; TYPE_2__* unconfirmed_connection_queue; TYPE_2__* incomming_connection_queue; int /*<<< orphan*/  secret_key; } ;
typedef  TYPE_1__ TCP_Server ;
typedef  TYPE_2__ TCP_Secure_Connection ;

/* Variables and functions */
 int MAX_INCOMMING_CONNECTIONS ; 
 scalar_t__ TCP_STATUS_CONNECTED ; 
 scalar_t__ TCP_STATUS_NO_STATUS ; 
 int /*<<< orphan*/  kill_TCP_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int read_connection_handshake (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_2__*,int) ; 

__attribute__((used)) static int do_incoming(TCP_Server *TCP_server, uint32_t i)
{
    if (TCP_server->incomming_connection_queue[i].status != TCP_STATUS_CONNECTED)
        return -1;

    int ret = read_connection_handshake(&TCP_server->incomming_connection_queue[i], TCP_server->secret_key);

    if (ret == -1) {
        kill_TCP_connection(&TCP_server->incomming_connection_queue[i]);
    } else if (ret == 1) {
        int index_new = TCP_server->unconfirmed_connection_queue_index % MAX_INCOMMING_CONNECTIONS;
        TCP_Secure_Connection *conn_old = &TCP_server->incomming_connection_queue[i];
        TCP_Secure_Connection *conn_new = &TCP_server->unconfirmed_connection_queue[index_new];

        if (conn_new->status != TCP_STATUS_NO_STATUS)
            kill_TCP_connection(conn_new);

        memcpy(conn_new, conn_old, sizeof(TCP_Secure_Connection));
        sodium_memzero(conn_old, sizeof(TCP_Secure_Connection));
        ++TCP_server->unconfirmed_connection_queue_index;

        return index_new;
    }

    return -1;
}