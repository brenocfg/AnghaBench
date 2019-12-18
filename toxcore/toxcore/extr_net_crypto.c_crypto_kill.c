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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {scalar_t__ status; int /*<<< orphan*/  recv_array; int /*<<< orphan*/  send_array; int /*<<< orphan*/  ip_portv6; int /*<<< orphan*/  ip_portv4; int /*<<< orphan*/  connection_number_tcp; } ;
struct TYPE_9__ {int /*<<< orphan*/  connections_mutex; int /*<<< orphan*/  ip_port_list; int /*<<< orphan*/  tcp_mutex; int /*<<< orphan*/  tcp_c; int /*<<< orphan*/  connection_use_counter; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  TYPE_2__ Crypto_Connection ;

/* Variables and functions */
 scalar_t__ CRYPTO_CONN_ESTABLISHED ; 
 int /*<<< orphan*/  bs_list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_temp_packet (TYPE_1__*,int) ; 
 TYPE_2__* get_crypto_connection (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kill_tcp_connection_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_kill_packet (TYPE_1__*,int) ; 
 int wipe_crypto_connection (TYPE_1__*,int) ; 

int crypto_kill(Net_Crypto *c, int crypt_connection_id)
{
    while (1) { /* TODO: is this really the best way to do this? */
        pthread_mutex_lock(&c->connections_mutex);

        if (!c->connection_use_counter) {
            break;
        }

        pthread_mutex_unlock(&c->connections_mutex);
    }

    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    int ret = -1;

    if (conn) {
        if (conn->status == CRYPTO_CONN_ESTABLISHED)
            send_kill_packet(c, crypt_connection_id);

        pthread_mutex_lock(&c->tcp_mutex);
        kill_tcp_connection_to(c->tcp_c, conn->connection_number_tcp);
        pthread_mutex_unlock(&c->tcp_mutex);

        bs_list_remove(&c->ip_port_list, (uint8_t *)&conn->ip_portv4, crypt_connection_id);
        bs_list_remove(&c->ip_port_list, (uint8_t *)&conn->ip_portv6, crypt_connection_id);
        clear_temp_packet(c, crypt_connection_id);
        clear_buffer(&conn->send_array);
        clear_buffer(&conn->recv_array);
        ret = wipe_crypto_connection(c, crypt_connection_id);
    }

    pthread_mutex_unlock(&c->connections_mutex);

    return ret;
}