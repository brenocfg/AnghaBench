#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  unsigned int uint16_t ;
struct TYPE_18__ {int /*<<< orphan*/  ip; } ;
struct TYPE_17__ {int /*<<< orphan*/  ip; } ;
struct TYPE_16__ {int /*<<< orphan*/  public_key; TYPE_8__ ip_port; } ;
struct TYPE_15__ {int num_friends; TYPE_2__* friends_list; int /*<<< orphan*/  last_pinged_index; int /*<<< orphan*/ * last_pinged; TYPE_1__* c; TYPE_3__* clients_announce_list; } ;
struct TYPE_14__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  timestamp; } ;
struct TYPE_13__ {int /*<<< orphan*/  last_pinged_index; int /*<<< orphan*/ * last_pinged; int /*<<< orphan*/ * real_public_key; TYPE_3__* clients_list; } ;
struct TYPE_12__ {int /*<<< orphan*/ * self_public_key; } ;
typedef  TYPE_3__ Onion_Node ;
typedef  TYPE_4__ Onion_Client ;
typedef  TYPE_5__ Node_format ;
typedef  int /*<<< orphan*/  Last_Pinged ;
typedef  TYPE_6__ IP_Port ;

/* Variables and functions */
 scalar_t__ LAN_ip (int /*<<< orphan*/ ) ; 
 unsigned int MAX_ONION_CLIENTS ; 
 unsigned int MAX_ONION_CLIENTS_ANNOUNCE ; 
 int /*<<< orphan*/  ONION_NODE_TIMEOUT ; 
 int /*<<< orphan*/  client_send_announce_request (TYPE_4__*,int,TYPE_8__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ good_to_ping (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int id_closest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_ping_nodes(Onion_Client *onion_c, uint32_t num, const Node_format *nodes, uint16_t num_nodes,
                             IP_Port source)
{
    if (num > onion_c->num_friends)
        return -1;

    if (num_nodes == 0)
        return 0;

    Onion_Node *list_nodes = NULL;
    uint8_t *reference_id = NULL;
    unsigned int list_length;

    Last_Pinged *last_pinged = NULL;
    uint8_t *last_pinged_index = NULL;

    if (num == 0) {
        list_nodes = onion_c->clients_announce_list;
        reference_id = onion_c->c->self_public_key;
        list_length = MAX_ONION_CLIENTS_ANNOUNCE;
        last_pinged = onion_c->last_pinged;
        last_pinged_index = &onion_c->last_pinged_index;
    } else {
        list_nodes = onion_c->friends_list[num - 1].clients_list;
        reference_id = onion_c->friends_list[num - 1].real_public_key;
        list_length = MAX_ONION_CLIENTS;
        last_pinged = onion_c->friends_list[num - 1].last_pinged;
        last_pinged_index = &onion_c->friends_list[num - 1].last_pinged_index;
    }

    unsigned int i, j;
    int lan_ips_accepted = (LAN_ip(source.ip) == 0);

    for (i = 0; i < num_nodes; ++i) {

        if (!lan_ips_accepted)
            if (LAN_ip(nodes[i].ip_port.ip) == 0)
                continue;

        if (is_timeout(list_nodes[0].timestamp, ONION_NODE_TIMEOUT)
                || id_closest(reference_id, list_nodes[0].public_key, nodes[i].public_key) == 2
                || is_timeout(list_nodes[1].timestamp, ONION_NODE_TIMEOUT)
                || id_closest(reference_id, list_nodes[1].public_key, nodes[i].public_key) == 2 ) {
            /* check if node is already in list. */
            for (j = 0; j < list_length; ++j) {
                if (public_key_cmp(list_nodes[j].public_key, nodes[i].public_key) == 0) {
                    break;
                }
            }

            if (j == list_length && good_to_ping(last_pinged, last_pinged_index, nodes[i].public_key)) {
                client_send_announce_request(onion_c, num, nodes[i].ip_port, nodes[i].public_key, NULL, ~0);
            }
        }
    }

    return 0;
}