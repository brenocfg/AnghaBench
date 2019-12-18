#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_8__ {int uint32; } ;
struct TYPE_9__ {TYPE_1__ ip4; void* family; } ;
struct TYPE_10__ {TYPE_2__ ip; } ;
struct TYPE_12__ {TYPE_3__ ip_port; } ;
struct TYPE_11__ {unsigned int path_nodes_index; unsigned int path_nodes_index_bs; TYPE_5__* path_nodes_bs; TYPE_5__* path_nodes; int /*<<< orphan*/  c; int /*<<< orphan*/  dht; } ;
typedef  TYPE_4__ Onion_Client ;
typedef  TYPE_5__ Node_format ;

/* Variables and functions */
 scalar_t__ DHT_isconnected (int /*<<< orphan*/ ) ; 
 unsigned int MAX_PATH_NODES ; 
 void* TCP_FAMILY ; 
 int get_random_tcp_con_number (int /*<<< orphan*/ ) ; 
 unsigned int rand () ; 

__attribute__((used)) static uint16_t random_nodes_path_onion(const Onion_Client *onion_c, Node_format *nodes, uint16_t max_num)
{
    unsigned int i;

    if (!max_num)
        return 0;

    unsigned int num_nodes = (onion_c->path_nodes_index < MAX_PATH_NODES) ? onion_c->path_nodes_index : MAX_PATH_NODES;

    //if (DHT_non_lan_connected(onion_c->dht)) {
    if (DHT_isconnected(onion_c->dht)) {
        if (num_nodes == 0)
            return 0;

        for (i = 0; i < max_num; ++i) {
            nodes[i] = onion_c->path_nodes[rand() % num_nodes];
        }
    } else {
        int random_tcp = get_random_tcp_con_number(onion_c->c);

        if (random_tcp == -1) {
            return 0;
        }

        if (num_nodes >= 2) {
            nodes[0].ip_port.ip.family = TCP_FAMILY;
            nodes[0].ip_port.ip.ip4.uint32 = random_tcp;

            for (i = 1; i < max_num; ++i) {
                nodes[i] = onion_c->path_nodes[rand() % num_nodes];
            }
        } else {
            unsigned int num_nodes_bs = (onion_c->path_nodes_index_bs < MAX_PATH_NODES) ? onion_c->path_nodes_index_bs :
                                        MAX_PATH_NODES;

            if (num_nodes_bs == 0)
                return 0;

            nodes[0].ip_port.ip.family = TCP_FAMILY;
            nodes[0].ip_port.ip.ip4.uint32 = random_tcp;

            for (i = 1; i < max_num; ++i) {
                nodes[i] = onion_c->path_nodes_bs[rand() % num_nodes_bs];
            }
        }
    }

    return max_num;
}