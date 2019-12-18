#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
struct TYPE_6__ {int /*<<< orphan*/  dht; } ;
typedef  TYPE_1__ Onion_Client ;
typedef  TYPE_2__ Node_format ;

/* Variables and functions */
 int MAX_FRIEND_CLIENTS ; 
 int /*<<< orphan*/  onion_add_path_node (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int randfriends_nodes (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static void populate_path_nodes(Onion_Client *onion_c)
{
    Node_format nodes_list[MAX_FRIEND_CLIENTS];

    unsigned int num_nodes = randfriends_nodes(onion_c->dht, nodes_list, MAX_FRIEND_CLIENTS);

    unsigned int i;

    for (i = 0; i < num_nodes; ++i) {
        onion_add_path_node(onion_c, nodes_list[i].ip_port, nodes_list[i].public_key);
    }
}