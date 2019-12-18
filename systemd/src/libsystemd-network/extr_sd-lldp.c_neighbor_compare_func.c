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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ sd_lldp_neighbor ;

/* Variables and functions */
 int lldp_neighbor_id_compare_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int neighbor_compare_func(sd_lldp_neighbor * const *a, sd_lldp_neighbor * const *b) {
        return lldp_neighbor_id_compare_func(&(*a)->id, &(*b)->id);
}