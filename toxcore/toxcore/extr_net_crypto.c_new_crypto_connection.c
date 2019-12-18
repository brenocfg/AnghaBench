#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cookie_request ;
struct TYPE_9__ {int connection_number_tcp; int /*<<< orphan*/  status; int /*<<< orphan*/  shared_key; int /*<<< orphan*/  cookie_request_number; int /*<<< orphan*/  dht_public_key; int /*<<< orphan*/  rtt_time; int /*<<< orphan*/  packets_left; void* packet_send_rate_requested; void* packet_send_rate; int /*<<< orphan*/  sessionsecret_key; int /*<<< orphan*/  sessionpublic_key; int /*<<< orphan*/  sent_nonce; int /*<<< orphan*/  public_key; } ;
struct TYPE_8__ {int /*<<< orphan*/  tcp_mutex; int /*<<< orphan*/  tcp_c; TYPE_2__* crypto_connections; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  TYPE_2__ Crypto_Connection ;

/* Variables and functions */
 int COOKIE_REQUEST_LENGTH ; 
 int /*<<< orphan*/  CRYPTO_CONN_COOKIE_REQUESTING ; 
 int /*<<< orphan*/  CRYPTO_CONN_NO_CONNECTION ; 
 int /*<<< orphan*/  CRYPTO_MIN_QUEUE_LENGTH ; 
 void* CRYPTO_PACKET_MIN_RATE ; 
 int /*<<< orphan*/  DEFAULT_PING_CONNECTION ; 
 int create_cookie_request (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int create_crypto_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  crypto_box_keypair (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getcryptconnection_id (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kill_tcp_connection_to (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int new_tcp_connection_to (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ new_temp_packet (TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_64b () ; 
 int /*<<< orphan*/  random_nonce (int /*<<< orphan*/ ) ; 

int new_crypto_connection(Net_Crypto *c, const uint8_t *real_public_key, const uint8_t *dht_public_key)
{
    int crypt_connection_id = getcryptconnection_id(c, real_public_key);

    if (crypt_connection_id != -1)
        return crypt_connection_id;

    crypt_connection_id = create_crypto_connection(c);

    if (crypt_connection_id == -1)
        return -1;

    Crypto_Connection *conn = &c->crypto_connections[crypt_connection_id];

    if (conn == 0)
        return -1;

    pthread_mutex_lock(&c->tcp_mutex);
    int connection_number_tcp = new_tcp_connection_to(c->tcp_c, dht_public_key, crypt_connection_id);
    pthread_mutex_unlock(&c->tcp_mutex);

    if (connection_number_tcp == -1)
        return -1;

    conn->connection_number_tcp = connection_number_tcp;
    memcpy(conn->public_key, real_public_key, crypto_box_PUBLICKEYBYTES);
    random_nonce(conn->sent_nonce);
    crypto_box_keypair(conn->sessionpublic_key, conn->sessionsecret_key);
    conn->status = CRYPTO_CONN_COOKIE_REQUESTING;
    conn->packet_send_rate = CRYPTO_PACKET_MIN_RATE;
    conn->packet_send_rate_requested = CRYPTO_PACKET_MIN_RATE;
    conn->packets_left = CRYPTO_MIN_QUEUE_LENGTH;
    conn->rtt_time = DEFAULT_PING_CONNECTION;
    memcpy(conn->dht_public_key, dht_public_key, crypto_box_PUBLICKEYBYTES);

    conn->cookie_request_number = random_64b();
    uint8_t cookie_request[COOKIE_REQUEST_LENGTH];

    if (create_cookie_request(c, cookie_request, conn->dht_public_key, conn->cookie_request_number,
                              conn->shared_key) != sizeof(cookie_request)
            || new_temp_packet(c, crypt_connection_id, cookie_request, sizeof(cookie_request)) != 0) {
        pthread_mutex_lock(&c->tcp_mutex);
        kill_tcp_connection_to(c->tcp_c, conn->connection_number_tcp);
        pthread_mutex_unlock(&c->tcp_mutex);
        conn->status = CRYPTO_CONN_NO_CONNECTION;
        return -1;
    }

    return crypt_connection_id;
}