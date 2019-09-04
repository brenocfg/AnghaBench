#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_3__ {unsigned int path_nodes_index; int /*<<< orphan*/ * path_nodes; } ;
typedef  TYPE_1__ Onion_Client ;
typedef  int /*<<< orphan*/  Node_format ;

/* Variables and functions */
 unsigned int MAX_PATH_NODES ; 

uint16_t onion_backup_nodes(const Onion_Client *onion_c, Node_format *nodes, uint16_t max_num)
{
    unsigned int i;

    if (!max_num)
        return 0;

    unsigned int num_nodes = (onion_c->path_nodes_index < MAX_PATH_NODES) ? onion_c->path_nodes_index : MAX_PATH_NODES;

    if (num_nodes == 0)
        return 0;

    if (num_nodes < max_num)
        max_num = num_nodes;

    for (i = 0; i < max_num; ++i) {
        nodes[i] = onion_c->path_nodes[(onion_c->path_nodes_index - (1 + i)) % num_nodes];
    }

    return max_num;
}