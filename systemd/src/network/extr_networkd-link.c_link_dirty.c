#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dirty_links; } ;
struct TYPE_7__ {TYPE_3__* manager; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_dirty (TYPE_3__*) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,TYPE_1__*) ; 

void link_dirty(Link *link) {
        int r;

        assert(link);

        /* mark manager dirty as link is dirty */
        manager_dirty(link->manager);

        r = set_ensure_allocated(&link->manager->dirty_links, NULL);
        if (r < 0)
                /* allocation errors are ignored */
                return;

        r = set_put(link->manager->dirty_links, link);
        if (r <= 0)
                /* don't take another ref if the link was already dirty */
                return;

        link_ref(link);
}