#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  state; TYPE_1__* manager; int /*<<< orphan*/  ifindex; } ;
struct TYPE_7__ {int /*<<< orphan*/  links_by_name; int /*<<< orphan*/  links; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 

Link *link_free(Link *l) {

        if (!l)
                return NULL;

        if (l->manager) {
                hashmap_remove(l->manager->links, INT_TO_PTR(l->ifindex));
                hashmap_remove(l->manager->links_by_name, l->ifname);
        }

        free(l->state);
        free(l->ifname);
        return mfree(l);
 }