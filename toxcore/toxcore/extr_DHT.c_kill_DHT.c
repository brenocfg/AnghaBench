#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* loaded_nodes_list; struct TYPE_5__* friends_list; int /*<<< orphan*/  ping; int /*<<< orphan*/  dht_harden_ping_array; int /*<<< orphan*/  dht_ping_array; int /*<<< orphan*/  net; int /*<<< orphan*/  assoc; } ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_PACKET_HARDENING ; 
 int /*<<< orphan*/  CRYPTO_PACKET_NAT_PING ; 
 int /*<<< orphan*/  NET_PACKET_GET_NODES ; 
 int /*<<< orphan*/  NET_PACKET_SEND_NODES_IPV6 ; 
 int /*<<< orphan*/  cryptopacket_registerhandler (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_Assoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_ping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ping_array_free_all (int /*<<< orphan*/ *) ; 

void kill_DHT(DHT *dht)
{
#ifdef ENABLE_ASSOC_DHT
    kill_Assoc(dht->assoc);
#endif
    networking_registerhandler(dht->net, NET_PACKET_GET_NODES, NULL, NULL);
    networking_registerhandler(dht->net, NET_PACKET_SEND_NODES_IPV6, NULL, NULL);
    cryptopacket_registerhandler(dht, CRYPTO_PACKET_NAT_PING, NULL, NULL);
    cryptopacket_registerhandler(dht, CRYPTO_PACKET_HARDENING, NULL, NULL);
    ping_array_free_all(&dht->dht_ping_array);
    ping_array_free_all(&dht->dht_harden_ping_array);
    kill_ping(dht->ping);
    free(dht->friends_list);
    free(dht->loaded_nodes_list);
    free(dht);
}