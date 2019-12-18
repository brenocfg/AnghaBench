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
typedef  int int32_t ;
struct TYPE_9__ {int crypt_connection_id; int onion_friendnum; int /*<<< orphan*/  real_public_key; int /*<<< orphan*/  status; int /*<<< orphan*/  lock_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  onion_c; TYPE_2__* conns; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  FRIENDCONN_STATUS_CONNECTING ; 
 int create_friend_conn (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  dht_pk_callback ; 
 int getfriend_conn_id_pk (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int onion_addfriend (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  onion_dht_pk_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  recv_tcp_relay_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  tcp_relay_node_callback ; 

int new_friend_connection(Friend_Connections *fr_c, const uint8_t *real_public_key)
{
    int friendcon_id = getfriend_conn_id_pk(fr_c, real_public_key);

    if (friendcon_id != -1) {
        ++fr_c->conns[friendcon_id].lock_count;
        return friendcon_id;
    }

    friendcon_id = create_friend_conn(fr_c);

    if (friendcon_id == -1)
        return -1;

    int32_t onion_friendnum = onion_addfriend(fr_c->onion_c, real_public_key);

    if (onion_friendnum == -1)
        return -1;

    Friend_Conn *friend_con = &fr_c->conns[friendcon_id];

    friend_con->crypt_connection_id = -1;
    friend_con->status = FRIENDCONN_STATUS_CONNECTING;
    memcpy(friend_con->real_public_key, real_public_key, crypto_box_PUBLICKEYBYTES);
    friend_con->onion_friendnum = onion_friendnum;

    recv_tcp_relay_handler(fr_c->onion_c, onion_friendnum, &tcp_relay_node_callback, fr_c, friendcon_id);
    onion_dht_pk_callback(fr_c->onion_c, onion_friendnum, &dht_pk_callback, fr_c, friendcon_id);

    return friendcon_id;
}