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
struct TYPE_7__ {TYPE_1__* manager; } ;
struct TYPE_6__ {int /*<<< orphan*/  address_pools; } ;
typedef  TYPE_2__ AddressPool ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  address_pools ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void address_pool_free(AddressPool *p) {

        if (!p)
                return;

        if (p->manager)
                LIST_REMOVE(address_pools, p->manager->address_pools, p);

        free(p);
}