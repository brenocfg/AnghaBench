#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {TYPE_1__* callbacks; int /*<<< orphan*/  ping_lastrecv; int /*<<< orphan*/  real_public_key; } ;
struct TYPE_11__ {int /*<<< orphan*/  fr_request_object; int /*<<< orphan*/  (* fr_request_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_callback_id; int /*<<< orphan*/  data_callback_object; int /*<<< orphan*/  (* data_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ Node_format ;
typedef  TYPE_3__ Friend_Connections ;
typedef  TYPE_4__ Friend_Conn ;

/* Variables and functions */
 unsigned int MAX_FRIEND_CONNECTION_CALLBACKS ; 
 int MAX_SHARED_RELAYS ; 
 scalar_t__ PACKET_ID_ALIVE ; 
 scalar_t__ PACKET_ID_FRIEND_REQUESTS ; 
 scalar_t__ PACKET_ID_SHARE_RELAYS ; 
 int /*<<< orphan*/  friend_add_tcp_relay (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_conn (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time () ; 
 int unpack_nodes (TYPE_2__*,int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_packet(void *object, int number, uint8_t *data, uint16_t length)
{
    if (length == 0)
        return -1;

    Friend_Connections *fr_c = object;
    Friend_Conn *friend_con = get_conn(fr_c, number);

    if (!friend_con)
        return -1;

    if (data[0] == PACKET_ID_FRIEND_REQUESTS) {
        if (fr_c->fr_request_callback)
            fr_c->fr_request_callback(fr_c->fr_request_object, friend_con->real_public_key, data, length);

        return 0;
    } else if (data[0] == PACKET_ID_ALIVE) {
        friend_con->ping_lastrecv = unix_time();
        return 0;
    } else if (data[0] == PACKET_ID_SHARE_RELAYS) {
        Node_format nodes[MAX_SHARED_RELAYS];
        int n;

        if ((n = unpack_nodes(nodes, MAX_SHARED_RELAYS, NULL, data + 1, length - 1, 1)) == -1)
            return -1;

        int j;

        for (j = 0; j < n; j++) {
            friend_add_tcp_relay(fr_c, number, nodes[j].ip_port, nodes[j].public_key);
        }

        return 0;
    }

    unsigned int i;

    for (i = 0; i < MAX_FRIEND_CONNECTION_CALLBACKS; ++i) {
        if (friend_con->callbacks[i].data_callback)
            friend_con->callbacks[i].data_callback(friend_con->callbacks[i].data_callback_object,
                                                   friend_con->callbacks[i].data_callback_id, data, length);

        friend_con = get_conn(fr_c, number);

        if (!friend_con)
            return -1;
    }

    return 0;
}