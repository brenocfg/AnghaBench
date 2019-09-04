#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {scalar_t__ status; scalar_t__ temp_packet_num_sent; } ;
struct TYPE_7__ {scalar_t__ crypto_connections_length; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  TYPE_2__ Crypto_Connection ;

/* Variables and functions */
 scalar_t__ CRYPTO_CONN_COOKIE_REQUESTING ; 
 scalar_t__ CRYPTO_CONN_ESTABLISHED ; 
 scalar_t__ CRYPTO_CONN_HANDSHAKE_SENT ; 
 scalar_t__ CRYPTO_CONN_NOT_CONFIRMED ; 
 scalar_t__ CRYPTO_CONN_NO_CONNECTION ; 
 scalar_t__ MAX_NUM_SENDPACKET_TRIES ; 
 int /*<<< orphan*/  connection_kill (TYPE_1__*,scalar_t__) ; 
 TYPE_2__* get_crypto_connection (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void kill_timedout(Net_Crypto *c)
{
    uint32_t i;
    //uint64_t temp_time = current_time_monotonic();

    for (i = 0; i < c->crypto_connections_length; ++i) {
        Crypto_Connection *conn = get_crypto_connection(c, i);

        if (conn == 0)
            return;

        if (conn->status == CRYPTO_CONN_NO_CONNECTION)
            continue;

        if (conn->status == CRYPTO_CONN_COOKIE_REQUESTING || conn->status == CRYPTO_CONN_HANDSHAKE_SENT
                || conn->status == CRYPTO_CONN_NOT_CONFIRMED) {
            if (conn->temp_packet_num_sent < MAX_NUM_SENDPACKET_TRIES)
                continue;

            connection_kill(c, i);

        }

        if (conn->status == CRYPTO_CONN_ESTABLISHED) {
            //TODO: add a timeout here?
        }
    }
}