#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  node_public_key3; int /*<<< orphan*/  node_public_key2; int /*<<< orphan*/  node_public_key1; int /*<<< orphan*/  ip_port3; int /*<<< orphan*/  ip_port2; int /*<<< orphan*/  ip_port1; } ;
typedef  TYPE_1__ Onion_Path ;
typedef  TYPE_2__ Node_format ;

/* Variables and functions */
 unsigned int ONION_PATH_LENGTH ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int onion_path_to_nodes(Node_format *nodes, unsigned int num_nodes, const Onion_Path *path)
{
    if (num_nodes < ONION_PATH_LENGTH)
        return -1;

    nodes[0].ip_port = path->ip_port1;
    nodes[1].ip_port = path->ip_port2;
    nodes[2].ip_port = path->ip_port3;

    memcpy(nodes[0].public_key, path->node_public_key1, crypto_box_PUBLICKEYBYTES);
    memcpy(nodes[1].public_key, path->node_public_key2, crypto_box_PUBLICKEYBYTES);
    memcpy(nodes[2].public_key, path->node_public_key3, crypto_box_PUBLICKEYBYTES);
    return 0;
}