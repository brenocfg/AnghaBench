#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  self_public_key; } ;
struct TYPE_13__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_11__ {int /*<<< orphan*/  family; } ;
struct TYPE_10__ {TYPE_2__ ip; } ;
struct TYPE_12__ {TYPE_1__ ip_port; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_3__ Node_format ;
typedef  TYPE_4__ IPPTsPng ;
typedef  TYPE_5__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 TYPE_4__* get_closelist_IPPTsPng (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t have_nodes_closelist(DHT *dht, Node_format *nodes, uint16_t num)
{
    uint32_t counter = 0;
    uint32_t i;

    for (i = 0; i < num; ++i) {
        if (id_equal(nodes[i].public_key, dht->self_public_key)) {
            ++counter;
            continue;
        }

        IPPTsPng *temp = get_closelist_IPPTsPng(dht, nodes[i].public_key, nodes[i].ip_port.ip.family);

        if (temp) {
            if (!is_timeout(temp->timestamp, BAD_NODE_TIMEOUT)) {
                ++counter;
            }
        }
    }

    return counter;
}