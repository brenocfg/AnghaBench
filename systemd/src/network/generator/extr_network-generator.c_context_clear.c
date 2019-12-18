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
struct TYPE_3__ {int /*<<< orphan*/  links_by_name; int /*<<< orphan*/  netdevs_by_name; int /*<<< orphan*/  networks_by_name; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_free ; 
 int /*<<< orphan*/  netdev_free ; 
 int /*<<< orphan*/  network_free ; 

void context_clear(Context *context) {
        if (!context)
                return;

        hashmap_free_with_destructor(context->networks_by_name, network_free);
        hashmap_free_with_destructor(context->netdevs_by_name, netdev_free);
        hashmap_free_with_destructor(context->links_by_name, link_free);
}