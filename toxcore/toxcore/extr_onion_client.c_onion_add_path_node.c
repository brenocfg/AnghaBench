#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ family; } ;
struct TYPE_10__ {TYPE_1__ ip; } ;
struct TYPE_9__ {unsigned int path_nodes_index; TYPE_2__* path_nodes; } ;
struct TYPE_8__ {int /*<<< orphan*/  public_key; TYPE_4__ ip_port; } ;
typedef  TYPE_3__ Onion_Client ;
typedef  TYPE_4__ IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 unsigned int MAX_PATH_NODES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int onion_add_path_node(Onion_Client *onion_c, IP_Port ip_port, const uint8_t *public_key)
{
    if (ip_port.ip.family != AF_INET && ip_port.ip.family != AF_INET6)
        return -1;

    unsigned int i;

    for (i = 0; i < MAX_PATH_NODES; ++i) {
        if (public_key_cmp(public_key, onion_c->path_nodes[i].public_key) == 0)
            return -1;
    }

    onion_c->path_nodes[onion_c->path_nodes_index % MAX_PATH_NODES].ip_port = ip_port;
    memcpy(onion_c->path_nodes[onion_c->path_nodes_index % MAX_PATH_NODES].public_key, public_key,
           crypto_box_PUBLICKEYBYTES);

    uint16_t last = onion_c->path_nodes_index;
    ++onion_c->path_nodes_index;

    if (onion_c->path_nodes_index < last)
        onion_c->path_nodes_index = MAX_PATH_NODES + 1;

    return 0;
}