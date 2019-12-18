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
struct TYPE_4__ {int /*<<< orphan*/  neighbor_by_id; } ;
typedef  TYPE_1__ sd_lldp ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lldp_flush_neighbors(sd_lldp *lldp) {
        assert(lldp);

        hashmap_clear(lldp->neighbor_by_id);
}