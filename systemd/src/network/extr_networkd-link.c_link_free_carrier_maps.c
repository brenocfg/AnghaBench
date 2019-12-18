#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bound_by_links; int /*<<< orphan*/  bound_to_links; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  link_free_bound_by_list (TYPE_1__*) ; 
 int /*<<< orphan*/  link_free_bound_to_list (TYPE_1__*) ; 

__attribute__((used)) static void link_free_carrier_maps(Link *link) {
        bool list_updated = false;

        assert(link);

        if (!hashmap_isempty(link->bound_to_links)) {
                link_free_bound_to_list(link);
                list_updated = true;
        }

        if (!hashmap_isempty(link->bound_by_links)) {
                link_free_bound_by_list(link);
                list_updated = true;
        }

        if (list_updated)
                link_dirty(link);

        return;
}