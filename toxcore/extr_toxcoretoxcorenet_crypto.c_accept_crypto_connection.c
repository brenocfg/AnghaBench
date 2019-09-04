#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int connection_number_tcp; int /*<<< orphan*/  rtt_time; int /*<<< orphan*/  packets_left; void* packet_send_rate_requested; void* packet_send_rate; int /*<<< orphan*/  dht_public_key; int /*<<< orphan*/  status; int /*<<< orphan*/  shared_key; int /*<<< orphan*/  sessionsecret_key; int /*<<< orphan*/  peersessionpublic_key; int /*<<< orphan*/  sessionpublic_key; int /*<<< orphan*/  sent_nonce; int /*<<< orphan*/  recv_nonce; int /*<<< orphan*/  public_key; } ;
struct TYPE_11__ {int /*<<< orphan*/  tcp_mutex; int /*<<< orphan*/  tcp_c; TYPE_3__* crypto_connections; } ;
struct TYPE_10__ {scalar_t__ cookie_length; int /*<<< orphan*/  source; int /*<<< orphan*/  dht_public_key; int /*<<< orphan*/  cookie; int /*<<< orphan*/  peersessionpublic_key; int /*<<< orphan*/  recv_nonce; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ New_Connection ;
typedef  TYPE_2__ Net_Crypto ;
typedef  TYPE_3__ Crypto_Connection ;

/* Variables and functions */
 scalar_t__ COOKIE_LENGTH ; 
 int /*<<< orphan*/  CRYPTO_CONN_NOT_CONFIRMED ; 
 int /*<<< orphan*/  CRYPTO_CONN_NO_CONNECTION ; 
 int /*<<< orphan*/  CRYPTO_MIN_QUEUE_LENGTH ; 
 void* CRYPTO_PACKET_MIN_RATE ; 
 int /*<<< orphan*/  DEFAULT_PING_CONNECTION ; 
 int create_crypto_connection (TYPE_2__*) ; 
 scalar_t__ create_send_handshake (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_box_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  crypto_box_keypair (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_connection_add_source (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encrypt_precompute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getcryptconnection_id (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_tcp_connection_to (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int new_tcp_connection_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_nonce (int /*<<< orphan*/ ) ; 

int accept_crypto_connection(Net_Crypto *c, New_Connection *n_c)
{
    if (getcryptconnection_id(c, n_c->public_key) != -1)
        return -1;

    int crypt_connection_id = create_crypto_connection(c);

    if (crypt_connection_id == -1)
        return -1;

    Crypto_Connection *conn = &c->crypto_connections[crypt_connection_id];

    if (n_c->cookie_length != COOKIE_LENGTH)
        return -1;

    pthread_mutex_lock(&c->tcp_mutex);
    int connection_number_tcp = new_tcp_connection_to(c->tcp_c, n_c->dht_public_key, crypt_connection_id);
    pthread_mutex_unlock(&c->tcp_mutex);

    if (connection_number_tcp == -1)
        return -1;

    conn->connection_number_tcp = connection_number_tcp;
    memcpy(conn->public_key, n_c->public_key, crypto_box_PUBLICKEYBYTES);
    memcpy(conn->recv_nonce, n_c->recv_nonce, crypto_box_NONCEBYTES);
    memcpy(conn->peersessionpublic_key, n_c->peersessionpublic_key, crypto_box_PUBLICKEYBYTES);
    random_nonce(conn->sent_nonce);
    crypto_box_keypair(conn->sessionpublic_key, conn->sessionsecret_key);
    encrypt_precompute(conn->peersessionpublic_key, conn->sessionsecret_key, conn->shared_key);
    conn->status = CRYPTO_CONN_NOT_CONFIRMED;

    if (create_send_handshake(c, crypt_connection_id, n_c->cookie, n_c->dht_public_key) != 0) {
        pthread_mutex_lock(&c->tcp_mutex);
        kill_tcp_connection_to(c->tcp_c, conn->connection_number_tcp);
        pthread_mutex_unlock(&c->tcp_mutex);
        conn->status = CRYPTO_CONN_NO_CONNECTION;
        return -1;
    }

    memcpy(conn->dht_public_key, n_c->dht_public_key, crypto_box_PUBLICKEYBYTES);
    conn->packet_send_rate = CRYPTO_PACKET_MIN_RATE;
    conn->packet_send_rate_requested = CRYPTO_PACKET_MIN_RATE;
    conn->packets_left = CRYPTO_MIN_QUEUE_LENGTH;
    conn->rtt_time = DEFAULT_PING_CONNECTION;
    crypto_connection_add_source(c, crypt_connection_id, n_c->source);
    return crypt_connection_id;
}