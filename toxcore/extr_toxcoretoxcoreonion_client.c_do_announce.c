#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
struct TYPE_7__ {unsigned int path_nodes_index; unsigned int path_nodes_index_bs; TYPE_3__* path_nodes; TYPE_3__* path_nodes_bs; int /*<<< orphan*/  onion_paths_self; TYPE_1__* clients_announce_list; } ;
struct TYPE_6__ {int timestamp; int last_pinged; int /*<<< orphan*/  path_used; int /*<<< orphan*/  ping_id; int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; scalar_t__ is_stored; } ;
typedef  TYPE_1__ Onion_Node ;
typedef  TYPE_2__ Onion_Client ;
typedef  TYPE_3__ Node_format ;

/* Variables and functions */
 unsigned int ANNOUNCE_INTERVAL_ANNOUNCED ; 
 unsigned int ANNOUNCE_INTERVAL_NOT_ANNOUNCED ; 
 unsigned int MAX_ONION_CLIENTS_ANNOUNCE ; 
 unsigned int MAX_PATH_NODES ; 
 unsigned int ONION_NODE_TIMEOUT ; 
 scalar_t__ client_send_announce_request (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_timeout (int,unsigned int) ; 
 scalar_t__ path_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int rand () ; 
 int unix_time () ; 

__attribute__((used)) static void do_announce(Onion_Client *onion_c)
{
    unsigned int i, count = 0;
    Onion_Node *list_nodes = onion_c->clients_announce_list;

    for (i = 0; i < MAX_ONION_CLIENTS_ANNOUNCE; ++i) {
        if (is_timeout(list_nodes[i].timestamp, ONION_NODE_TIMEOUT))
            continue;

        ++count;

        /* Don't announce ourselves the first time this is run to new peers */
        if (list_nodes[i].last_pinged == 0) {
            list_nodes[i].last_pinged = 1;
            continue;
        }

        unsigned int interval = ANNOUNCE_INTERVAL_NOT_ANNOUNCED;

        if (list_nodes[i].is_stored && path_exists(&onion_c->onion_paths_self, list_nodes[i].path_used)) {
            interval = ANNOUNCE_INTERVAL_ANNOUNCED;
        }

        if (is_timeout(list_nodes[i].last_pinged, interval)) {
            if (client_send_announce_request(onion_c, 0, list_nodes[i].ip_port, list_nodes[i].public_key,
                                             list_nodes[i].ping_id, list_nodes[i].path_used) == 0) {
                list_nodes[i].last_pinged = unix_time();
            }
        }
    }

    if (count != MAX_ONION_CLIENTS_ANNOUNCE) {
        unsigned int num_nodes;
        Node_format *path_nodes;

        if (rand() % 2 == 0 || onion_c->path_nodes_index == 0) {
            num_nodes = (onion_c->path_nodes_index_bs < MAX_PATH_NODES) ? onion_c->path_nodes_index_bs : MAX_PATH_NODES;
            path_nodes = onion_c->path_nodes_bs;
        } else {
            num_nodes = (onion_c->path_nodes_index < MAX_PATH_NODES) ? onion_c->path_nodes_index : MAX_PATH_NODES;
            path_nodes = onion_c->path_nodes;
        }

        if (count < (uint32_t)rand() % MAX_ONION_CLIENTS_ANNOUNCE) {
            if (num_nodes != 0) {
                for (i = 0; i < (MAX_ONION_CLIENTS_ANNOUNCE / 2); ++i) {
                    unsigned int num = rand() % num_nodes;
                    client_send_announce_request(onion_c, 0, path_nodes[num].ip_port, path_nodes[num].public_key, 0, ~0);
                }
            }
        }
    }
}