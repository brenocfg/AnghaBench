#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dirty_links; struct TYPE_5__* manager; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 

void link_clean(Link *link) {
        assert(link);
        assert(link->manager);

        link_unref(set_remove(link->manager->dirty_links, link));
}