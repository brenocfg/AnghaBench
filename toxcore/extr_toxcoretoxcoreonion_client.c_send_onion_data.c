#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  o_packet ;
struct TYPE_11__ {scalar_t__ num_friends; TYPE_2__* friends_list; int /*<<< orphan*/  onion_paths_friends; TYPE_1__* c; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip_port; int /*<<< orphan*/  data_public_key; scalar_t__ is_stored; int /*<<< orphan*/  timestamp; } ;
struct TYPE_9__ {int /*<<< orphan*/  real_public_key; TYPE_3__* clients_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  self_secret_key; int /*<<< orphan*/  self_public_key; } ;
typedef  int /*<<< orphan*/  Onion_Path ;
typedef  TYPE_3__ Onion_Node ;
typedef  TYPE_4__ Onion_Client ;

/* Variables and functions */
 scalar_t__ DATA_IN_RESPONSE_MIN_SIZE ; 
 scalar_t__ MAX_DATA_REQUEST_SIZE ; 
 int MAX_ONION_CLIENTS ; 
 int ONION_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  ONION_NODE_TIMEOUT ; 
 int create_data_request (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int encrypt_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  random_nonce (int /*<<< orphan*/ *) ; 
 int random_path (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ send_onion_packet_tcp_udp (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int send_onion_data(Onion_Client *onion_c, int friend_num, const uint8_t *data, uint16_t length)
{
    if ((uint32_t)friend_num >= onion_c->num_friends)
        return -1;

    if (length + DATA_IN_RESPONSE_MIN_SIZE > MAX_DATA_REQUEST_SIZE)
        return -1;

    if (length == 0)
        return -1;

    unsigned int i, good_nodes[MAX_ONION_CLIENTS], num_good = 0, num_nodes = 0;
    Onion_Node *list_nodes = onion_c->friends_list[friend_num].clients_list;

    for (i = 0; i < MAX_ONION_CLIENTS; ++i) {
        if (is_timeout(list_nodes[i].timestamp, ONION_NODE_TIMEOUT))
            continue;

        ++num_nodes;

        if (list_nodes[i].is_stored) {
            good_nodes[num_good] = i;
            ++num_good;
        }
    }

    if (num_good < (num_nodes / 4) + 1)
        return -1;

    uint8_t nonce[crypto_box_NONCEBYTES];
    random_nonce(nonce);

    uint8_t packet[DATA_IN_RESPONSE_MIN_SIZE + length];
    memcpy(packet, onion_c->c->self_public_key, crypto_box_PUBLICKEYBYTES);
    int len = encrypt_data(onion_c->friends_list[friend_num].real_public_key, onion_c->c->self_secret_key, nonce, data,
                           length, packet + crypto_box_PUBLICKEYBYTES);

    if ((uint32_t)len + crypto_box_PUBLICKEYBYTES != sizeof(packet))
        return -1;

    unsigned int good = 0;

    for (i = 0; i < num_good; ++i) {
        Onion_Path path;

        if (random_path(onion_c, &onion_c->onion_paths_friends, ~0, &path) == -1)
            continue;

        uint8_t o_packet[ONION_MAX_PACKET_SIZE];
        len = create_data_request(o_packet, sizeof(o_packet), onion_c->friends_list[friend_num].real_public_key,
                                  list_nodes[good_nodes[i]].data_public_key, nonce, packet, sizeof(packet));

        if (len == -1)
            continue;

        if (send_onion_packet_tcp_udp(onion_c, &path, list_nodes[good_nodes[i]].ip_port, o_packet, len) == 0)
            ++good;
    }

    return good;
}