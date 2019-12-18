#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  nodes ;
struct TYPE_6__ {int name_length; int statusmessage_length; int /*<<< orphan*/  onion_c; int /*<<< orphan*/  net_crypto; int /*<<< orphan*/  dht; int /*<<< orphan*/  userstatus; int /*<<< orphan*/  statusmessage; int /*<<< orphan*/  name; int /*<<< orphan*/  fr; } ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  DHT_save (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DHT_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESSENGER_STATE_COOKIE_GLOBAL ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_DHT ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_END ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_FRIENDS ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_NAME ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_NOSPAMKEYS ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_PATH_NODE ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_STATUS ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_STATUSMESSAGE ; 
 int /*<<< orphan*/  MESSENGER_STATE_TYPE_TCP_RELAY ; 
 int NUM_SAVED_PATH_NODES ; 
 int NUM_SAVED_TCP_RELAYS ; 
 int /*<<< orphan*/  TCP_INET6 ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int copy_connected_tcp_relays (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  friends_list_save (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int get_nospam (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_to_lendian32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int messenger_size (TYPE_1__ const*) ; 
 unsigned int onion_backup_nodes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pack_nodes (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned int) ; 
 int packed_node_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int saved_friendslist_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * z_state_save_subheader (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void messenger_save(const Messenger *m, uint8_t *data)
{
    memset(data, 0, messenger_size(m));

    uint32_t len;
    uint16_t type;
    uint32_t size32 = sizeof(uint32_t);

    memset(data, 0, size32);
    data += size32;
    host_to_lendian32(data, MESSENGER_STATE_COOKIE_GLOBAL);
    data += size32;

#ifdef DEBUG
    assert(sizeof(get_nospam(&(m->fr))) == sizeof(uint32_t));
#endif
    len = size32 + crypto_box_PUBLICKEYBYTES + crypto_box_SECRETKEYBYTES;
    type = MESSENGER_STATE_TYPE_NOSPAMKEYS;
    data = z_state_save_subheader(data, len, type);
    *(uint32_t *)data = get_nospam(&(m->fr));
    save_keys(m->net_crypto, data + size32);
    data += len;

    len = saved_friendslist_size(m);
    type = MESSENGER_STATE_TYPE_FRIENDS;
    data = z_state_save_subheader(data, len, type);
    friends_list_save(m, data);
    data += len;

    len = m->name_length;
    type = MESSENGER_STATE_TYPE_NAME;
    data = z_state_save_subheader(data, len, type);
    memcpy(data, m->name, len);
    data += len;

    len = m->statusmessage_length;
    type = MESSENGER_STATE_TYPE_STATUSMESSAGE;
    data = z_state_save_subheader(data, len, type);
    memcpy(data, m->statusmessage, len);
    data += len;

    len = 1;
    type = MESSENGER_STATE_TYPE_STATUS;
    data = z_state_save_subheader(data, len, type);
    *data = m->userstatus;
    data += len;

    len = DHT_size(m->dht);
    type = MESSENGER_STATE_TYPE_DHT;
    data = z_state_save_subheader(data, len, type);
    DHT_save(m->dht, data);
    data += len;

    Node_format relays[NUM_SAVED_TCP_RELAYS];
    type = MESSENGER_STATE_TYPE_TCP_RELAY;
    uint8_t *temp_data = data;
    data = z_state_save_subheader(temp_data, 0, type);
    unsigned int num = copy_connected_tcp_relays(m->net_crypto, relays, NUM_SAVED_TCP_RELAYS);
    int l = pack_nodes(data, NUM_SAVED_TCP_RELAYS * packed_node_size(TCP_INET6), relays, num);

    if (l > 0) {
        len = l;
        data = z_state_save_subheader(temp_data, len, type);
        data += len;
    }

    Node_format nodes[NUM_SAVED_PATH_NODES];
    type = MESSENGER_STATE_TYPE_PATH_NODE;
    temp_data = data;
    data = z_state_save_subheader(data, 0, type);
    memset(nodes, 0, sizeof(nodes));
    num = onion_backup_nodes(m->onion_c, nodes, NUM_SAVED_PATH_NODES);
    l = pack_nodes(data, NUM_SAVED_PATH_NODES * packed_node_size(TCP_INET6), nodes, num);

    if (l > 0) {
        len = l;
        data = z_state_save_subheader(temp_data, len, type);
        data += len;
    }

    z_state_save_subheader(data, 0, MESSENGER_STATE_TYPE_END);
}