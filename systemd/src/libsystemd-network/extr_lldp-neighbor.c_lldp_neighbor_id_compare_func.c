#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  port_id_size; int /*<<< orphan*/  port_id; int /*<<< orphan*/  chassis_id_size; int /*<<< orphan*/  chassis_id; } ;
typedef  TYPE_1__ LLDPNeighborID ;

/* Variables and functions */
 int memcmp_nn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lldp_neighbor_id_compare_func(const LLDPNeighborID *x, const LLDPNeighborID *y) {
        return memcmp_nn(x->chassis_id, x->chassis_id_size, y->chassis_id, y->chassis_id_size)
            ?: memcmp_nn(x->port_id, x->port_id_size, y->port_id, y->port_id_size);
}