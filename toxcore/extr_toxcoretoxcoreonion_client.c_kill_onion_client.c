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
struct TYPE_9__ {TYPE_1__* c; int /*<<< orphan*/  dht; int /*<<< orphan*/  net; int /*<<< orphan*/  announce_ping_array; } ;
struct TYPE_8__ {int /*<<< orphan*/  tcp_c; } ;
typedef  TYPE_2__ Onion_Client ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_PACKET_DHTPK ; 
 int /*<<< orphan*/  NET_PACKET_ANNOUNCE_RESPONSE ; 
 int /*<<< orphan*/  NET_PACKET_ONION_DATA_RESPONSE ; 
 int /*<<< orphan*/  ONION_DATA_DHTPK ; 
 int /*<<< orphan*/  cryptopacket_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oniondata_registerhandler (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ping_array_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realloc_onion_friends (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_onion_packet_tcp_connection_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_2__*,int) ; 

void kill_onion_client(Onion_Client *onion_c)
{
    if (onion_c == NULL)
        return;

    ping_array_free_all(&onion_c->announce_ping_array);
    realloc_onion_friends(onion_c, 0);
    networking_registerhandler(onion_c->net, NET_PACKET_ANNOUNCE_RESPONSE, NULL, NULL);
    networking_registerhandler(onion_c->net, NET_PACKET_ONION_DATA_RESPONSE, NULL, NULL);
    oniondata_registerhandler(onion_c, ONION_DATA_DHTPK, NULL, NULL);
    cryptopacket_registerhandler(onion_c->dht, CRYPTO_PACKET_DHTPK, NULL, NULL);
    set_onion_packet_tcp_connection_callback(onion_c->c->tcp_c, NULL, NULL);
    sodium_memzero(onion_c, sizeof(Onion_Client));
    free(onion_c);
}