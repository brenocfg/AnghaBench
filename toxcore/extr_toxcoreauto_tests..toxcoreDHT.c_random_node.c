#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  nodes_list ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 int MAX_SENT_NODES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int get_close_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rand () ; 

Node_format random_node(DHT *dht, sa_family_t sa_family)
{
    uint8_t id[crypto_box_PUBLICKEYBYTES];
    uint32_t i;

    for (i = 0; i < crypto_box_PUBLICKEYBYTES / 4; ++i) { /* populate the id with pseudorandom bytes.*/
        uint32_t t = rand();
        memcpy(id + i * sizeof(t), &t, sizeof(t));
    }

    Node_format nodes_list[MAX_SENT_NODES];
    memset(nodes_list, 0, sizeof(nodes_list));
    uint32_t num_nodes = get_close_nodes(dht, id, nodes_list, sa_family, 1, 0);

    if (num_nodes == 0)
        return nodes_list[0];
    else
        return nodes_list[rand() % num_nodes];
}