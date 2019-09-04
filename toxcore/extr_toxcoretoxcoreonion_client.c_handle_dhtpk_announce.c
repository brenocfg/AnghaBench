#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  no_replay ;
struct TYPE_10__ {scalar_t__ family; } ;
struct TYPE_14__ {TYPE_1__ ip; } ;
struct TYPE_13__ {int /*<<< orphan*/  public_key; TYPE_6__ ip_port; } ;
struct TYPE_12__ {TYPE_2__* friends_list; int /*<<< orphan*/  dht; } ;
struct TYPE_11__ {scalar_t__ last_noreplay; int /*<<< orphan*/  (* tcp_relay_node_callback ) (void*,int /*<<< orphan*/ ,TYPE_6__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tcp_relay_node_callback_number; void* tcp_relay_node_callback_object; int /*<<< orphan*/  dht_public_key; int /*<<< orphan*/  last_seen; int /*<<< orphan*/  dht_pk_callback_number; int /*<<< orphan*/  dht_pk_callback_object; int /*<<< orphan*/  (* dht_pk_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*) ;} ;
typedef  TYPE_3__ Onion_Client ;
typedef  TYPE_4__ Node_format ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ DHTPK_DATA_MAX_LENGTH ; 
 scalar_t__ DHTPK_DATA_MIN_LENGTH ; 
 int /*<<< orphan*/  DHT_getnodes (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_SENT_NODES ; 
 scalar_t__ TCP_INET ; 
 scalar_t__ TCP_INET6 ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  net_to_host (scalar_t__*,int) ; 
 int onion_friend_num (TYPE_3__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  onion_set_friend_DHT_pubkey (TYPE_3__*,int,scalar_t__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ,TYPE_6__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time () ; 
 int unpack_nodes (TYPE_4__*,int,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__,int) ; 

__attribute__((used)) static int handle_dhtpk_announce(void *object, const uint8_t *source_pubkey, const uint8_t *data, uint16_t length)
{
    Onion_Client *onion_c = object;

    if (length < DHTPK_DATA_MIN_LENGTH)
        return 1;

    if (length > DHTPK_DATA_MAX_LENGTH)
        return 1;

    int friend_num = onion_friend_num(onion_c, source_pubkey);

    if (friend_num == -1)
        return 1;

    uint64_t no_replay;
    memcpy(&no_replay, data + 1, sizeof(uint64_t));
    net_to_host((uint8_t *) &no_replay, sizeof(no_replay));

    if (no_replay <= onion_c->friends_list[friend_num].last_noreplay)
        return 1;

    onion_c->friends_list[friend_num].last_noreplay = no_replay;

    if (onion_c->friends_list[friend_num].dht_pk_callback)
        onion_c->friends_list[friend_num].dht_pk_callback(onion_c->friends_list[friend_num].dht_pk_callback_object,
                onion_c->friends_list[friend_num].dht_pk_callback_number, data + 1 + sizeof(uint64_t));

    onion_set_friend_DHT_pubkey(onion_c, friend_num, data + 1 + sizeof(uint64_t));
    onion_c->friends_list[friend_num].last_seen = unix_time();

    uint16_t len_nodes = length - DHTPK_DATA_MIN_LENGTH;

    if (len_nodes != 0) {
        Node_format nodes[MAX_SENT_NODES];
        int num_nodes = unpack_nodes(nodes, MAX_SENT_NODES, 0, data + 1 + sizeof(uint64_t) + crypto_box_PUBLICKEYBYTES,
                                     len_nodes, 1);

        if (num_nodes <= 0)
            return 1;

        int i;

        for (i = 0; i < num_nodes; ++i) {
            uint8_t family = nodes[i].ip_port.ip.family;

            if (family == AF_INET || family == AF_INET6) {
                DHT_getnodes(onion_c->dht, &nodes[i].ip_port, nodes[i].public_key, onion_c->friends_list[friend_num].dht_public_key);
            } else if (family == TCP_INET || family == TCP_INET6) {
                if (onion_c->friends_list[friend_num].tcp_relay_node_callback) {
                    void *obj = onion_c->friends_list[friend_num].tcp_relay_node_callback_object;
                    uint32_t number = onion_c->friends_list[friend_num].tcp_relay_node_callback_number;
                    onion_c->friends_list[friend_num].tcp_relay_node_callback(obj, number, nodes[i].ip_port, nodes[i].public_key);
                }
            }
        }
    }

    return 0;
}