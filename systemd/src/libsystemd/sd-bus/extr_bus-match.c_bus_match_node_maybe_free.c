#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  children; } ;
struct bus_match_node {scalar_t__ type; TYPE_1__ compare; scalar_t__ child; } ;

/* Variables and functions */
 scalar_t__ BUS_MATCH_IS_COMPARE (scalar_t__) ; 
 scalar_t__ BUS_MATCH_ROOT ; 
 int /*<<< orphan*/  assert (struct bus_match_node*) ; 
 int /*<<< orphan*/  bus_match_node_free (struct bus_match_node*) ; 
 int /*<<< orphan*/  hashmap_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bus_match_node_maybe_free(struct bus_match_node *node) {
        assert(node);

        if (node->type == BUS_MATCH_ROOT)
                return false;

        if (node->child)
                return false;

        if (BUS_MATCH_IS_COMPARE(node->type) && !hashmap_isempty(node->compare.children))
                return true;

        bus_match_node_free(node);
        return true;
}