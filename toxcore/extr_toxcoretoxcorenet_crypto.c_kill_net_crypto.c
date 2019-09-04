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
struct TYPE_8__ {scalar_t__ crypto_connections_length; TYPE_1__* dht; int /*<<< orphan*/  ip_port_list; int /*<<< orphan*/  tcp_c; int /*<<< orphan*/  connections_mutex; int /*<<< orphan*/  tcp_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  net; } ;
typedef  TYPE_2__ Net_Crypto ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_COOKIE_REQUEST ; 
 int /*<<< orphan*/  NET_PACKET_COOKIE_RESPONSE ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO_DATA ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO_HS ; 
 int /*<<< orphan*/  bs_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_kill (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  kill_tcp_connections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_2__*,int) ; 

void kill_net_crypto(Net_Crypto *c)
{
    uint32_t i;

    for (i = 0; i < c->crypto_connections_length; ++i) {
        crypto_kill(c, i);
    }

    pthread_mutex_destroy(&c->tcp_mutex);
    pthread_mutex_destroy(&c->connections_mutex);

    kill_tcp_connections(c->tcp_c);
    bs_list_free(&c->ip_port_list);
    networking_registerhandler(c->dht->net, NET_PACKET_COOKIE_REQUEST, NULL, NULL);
    networking_registerhandler(c->dht->net, NET_PACKET_COOKIE_RESPONSE, NULL, NULL);
    networking_registerhandler(c->dht->net, NET_PACKET_CRYPTO_HS, NULL, NULL);
    networking_registerhandler(c->dht->net, NET_PACKET_CRYPTO_DATA, NULL, NULL);
    sodium_memzero(c, sizeof(Net_Crypto));
    free(c);
}