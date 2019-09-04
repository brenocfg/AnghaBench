#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int path_nodes_index; TYPE_1__* clients_announce_list; int /*<<< orphan*/  last_packet_recv; } ;
struct TYPE_4__ {scalar_t__ is_stored; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ Onion_Client ;

/* Variables and functions */
 unsigned int MAX_ONION_CLIENTS_ANNOUNCE ; 
 int /*<<< orphan*/  ONION_NODE_TIMEOUT ; 
 int /*<<< orphan*/  ONION_OFFLINE_TIMEOUT ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int onion_isconnected(const Onion_Client *onion_c)
{
    unsigned int i, num = 0, announced = 0;

    if (is_timeout(onion_c->last_packet_recv, ONION_OFFLINE_TIMEOUT))
        return 0;

    if (onion_c->path_nodes_index == 0)
        return 0;

    for (i = 0; i < MAX_ONION_CLIENTS_ANNOUNCE; ++i) {
        if (!is_timeout(onion_c->clients_announce_list[i].timestamp, ONION_NODE_TIMEOUT)) {
            ++num;

            if (onion_c->clients_announce_list[i].is_stored) {
                ++announced;
            }
        }
    }

    unsigned int pnodes = onion_c->path_nodes_index;

    if (pnodes > MAX_ONION_CLIENTS_ANNOUNCE) {
        pnodes = MAX_ONION_CLIENTS_ANNOUNCE;
    }

    /* Consider ourselves online if we are announced to half or more nodes
      we are connected to */
    if (num && announced) {
        if ((num / 2) <= announced && (pnodes / 2) <= num)
            return 1;
    }

    return 0;
}