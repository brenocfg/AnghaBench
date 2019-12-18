#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ifindex; TYPE_1__* manager; } ;
struct TYPE_9__ {int /*<<< orphan*/  links; int /*<<< orphan*/  links_requesting_uuid; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 TYPE_2__* hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_clean (TYPE_2__*) ; 
 int /*<<< orphan*/  link_unref (TYPE_2__*) ; 
 TYPE_2__* set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void link_detach_from_manager(Link *link) {
        if (!link || !link->manager)
                return;

        link_unref(set_remove(link->manager->links_requesting_uuid, link));
        link_clean(link);

        /* The following must be called at last. */
        assert_se(hashmap_remove(link->manager->links, INT_TO_PTR(link->ifindex)) == link);
        link_unref(link);
}