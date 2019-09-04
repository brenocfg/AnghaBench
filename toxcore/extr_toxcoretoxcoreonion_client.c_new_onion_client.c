#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  tcp_c; TYPE_10__* dht; } ;
struct TYPE_14__ {TYPE_2__* c; TYPE_10__* dht; int /*<<< orphan*/  net; int /*<<< orphan*/  temp_secret_key; int /*<<< orphan*/  temp_public_key; int /*<<< orphan*/  secret_symmetric_key; int /*<<< orphan*/  announce_ping_array; } ;
struct TYPE_13__ {int /*<<< orphan*/  net; } ;
typedef  TYPE_1__ Onion_Client ;
typedef  TYPE_2__ Net_Crypto ;

/* Variables and functions */
 int /*<<< orphan*/  ANNOUNCE_ARRAY_SIZE ; 
 int /*<<< orphan*/  ANNOUNCE_TIMEOUT ; 
 int /*<<< orphan*/  CRYPTO_PACKET_DHTPK ; 
 int /*<<< orphan*/  NET_PACKET_ANNOUNCE_RESPONSE ; 
 int /*<<< orphan*/  NET_PACKET_ONION_DATA_RESPONSE ; 
 int /*<<< orphan*/  ONION_DATA_DHTPK ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  crypto_box_keypair (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cryptopacket_registerhandler (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_announce_response ; 
 int /*<<< orphan*/  handle_data_response ; 
 int /*<<< orphan*/  handle_dht_dhtpk ; 
 int /*<<< orphan*/  handle_dhtpk_announce ; 
 int /*<<< orphan*/  handle_tcp_onion ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  new_symmetric_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oniondata_registerhandler (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ping_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_onion_packet_tcp_connection_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

Onion_Client *new_onion_client(Net_Crypto *c)
{
    if (c == NULL)
        return NULL;

    Onion_Client *onion_c = calloc(1, sizeof(Onion_Client));

    if (onion_c == NULL)
        return NULL;

    if (ping_array_init(&onion_c->announce_ping_array, ANNOUNCE_ARRAY_SIZE, ANNOUNCE_TIMEOUT) != 0) {
        free(onion_c);
        return NULL;
    }

    onion_c->dht = c->dht;
    onion_c->net = c->dht->net;
    onion_c->c = c;
    new_symmetric_key(onion_c->secret_symmetric_key);
    crypto_box_keypair(onion_c->temp_public_key, onion_c->temp_secret_key);
    networking_registerhandler(onion_c->net, NET_PACKET_ANNOUNCE_RESPONSE, &handle_announce_response, onion_c);
    networking_registerhandler(onion_c->net, NET_PACKET_ONION_DATA_RESPONSE, &handle_data_response, onion_c);
    oniondata_registerhandler(onion_c, ONION_DATA_DHTPK, &handle_dhtpk_announce, onion_c);
    cryptopacket_registerhandler(onion_c->dht, CRYPTO_PACKET_DHTPK, &handle_dht_dhtpk, onion_c);
    set_onion_packet_tcp_connection_callback(onion_c->c->tcp_c, &handle_tcp_onion, onion_c);

    return onion_c;
}