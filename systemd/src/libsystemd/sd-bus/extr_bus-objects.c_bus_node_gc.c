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
struct node {struct node* parent; struct node* path; scalar_t__ child; scalar_t__ object_managers; scalar_t__ enumerators; scalar_t__ vtables; scalar_t__ callbacks; } ;
struct TYPE_4__ {int /*<<< orphan*/  nodes; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,scalar_t__,struct node*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  free (struct node*) ; 
 struct node* hashmap_remove (int /*<<< orphan*/ ,struct node*) ; 
 int /*<<< orphan*/  siblings ; 

void bus_node_gc(sd_bus *b, struct node *n) {
        assert(b);

        if (!n)
                return;

        if (n->child ||
            n->callbacks ||
            n->vtables ||
            n->enumerators ||
            n->object_managers)
                return;

        assert_se(hashmap_remove(b->nodes, n->path) == n);

        if (n->parent)
                LIST_REMOVE(siblings, n->parent->child, n);

        free(n->path);
        bus_node_gc(b, n->parent);
        free(n);
}