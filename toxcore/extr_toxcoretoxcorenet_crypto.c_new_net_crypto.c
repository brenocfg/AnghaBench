#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  net; int /*<<< orphan*/  self_secret_key; } ;
struct TYPE_11__ {int /*<<< orphan*/  ip_port_list; int /*<<< orphan*/  current_sleep_time; int /*<<< orphan*/  secret_symmetric_key; TYPE_2__* dht; int /*<<< orphan*/ * tcp_c; int /*<<< orphan*/  connections_mutex; int /*<<< orphan*/  tcp_mutex; } ;
typedef  int /*<<< orphan*/  TCP_Proxy_Info ;
typedef  TYPE_1__ Net_Crypto ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_SEND_PACKET_INTERVAL ; 
 int /*<<< orphan*/  NET_PACKET_COOKIE_REQUEST ; 
 int /*<<< orphan*/  NET_PACKET_COOKIE_RESPONSE ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO_DATA ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO_HS ; 
 int /*<<< orphan*/  bs_list_init (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__ create_recursive_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_tcp_connections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  new_keys (TYPE_1__*) ; 
 int /*<<< orphan*/  new_symmetric_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_tcp_connections (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_oob_packet_tcp_connection_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_packet_tcp_connection_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tcp_data_callback ; 
 int /*<<< orphan*/  tcp_oob_callback ; 
 int /*<<< orphan*/  udp_handle_cookie_request ; 
 int /*<<< orphan*/  udp_handle_packet ; 
 int /*<<< orphan*/  unix_time_update () ; 

Net_Crypto *new_net_crypto(DHT *dht, TCP_Proxy_Info *proxy_info)
{
    unix_time_update();

    if (dht == NULL)
        return NULL;

    Net_Crypto *temp = calloc(1, sizeof(Net_Crypto));

    if (temp == NULL)
        return NULL;

    temp->tcp_c = new_tcp_connections(dht->self_secret_key, proxy_info);

    if (temp->tcp_c == NULL) {
        free(temp);
        return NULL;
    }

    set_packet_tcp_connection_callback(temp->tcp_c, &tcp_data_callback, temp);
    set_oob_packet_tcp_connection_callback(temp->tcp_c, &tcp_oob_callback, temp);

    if (create_recursive_mutex(&temp->tcp_mutex) != 0 ||
            pthread_mutex_init(&temp->connections_mutex, NULL) != 0) {
        kill_tcp_connections(temp->tcp_c);
        free(temp);
        return NULL;
    }

    temp->dht = dht;

    new_keys(temp);
    new_symmetric_key(temp->secret_symmetric_key);

    temp->current_sleep_time = CRYPTO_SEND_PACKET_INTERVAL;

    networking_registerhandler(dht->net, NET_PACKET_COOKIE_REQUEST, &udp_handle_cookie_request, temp);
    networking_registerhandler(dht->net, NET_PACKET_COOKIE_RESPONSE, &udp_handle_packet, temp);
    networking_registerhandler(dht->net, NET_PACKET_CRYPTO_HS, &udp_handle_packet, temp);
    networking_registerhandler(dht->net, NET_PACKET_CRYPTO_DATA, &udp_handle_packet, temp);

    bs_list_init(&temp->ip_port_list, sizeof(IP_Port), 8);

    return temp;
}