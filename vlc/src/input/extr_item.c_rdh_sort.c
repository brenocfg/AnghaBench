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
struct TYPE_4__ {scalar_t__ i_children; struct TYPE_4__** pp_children; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (TYPE_1__**,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdh_compar_filename ; 

__attribute__((used)) static void rdh_sort(input_item_node_t *p_node)
{
    if (p_node->i_children <= 0)
        return;

    /* Sort current node */
    qsort(p_node->pp_children, p_node->i_children,
          sizeof(input_item_node_t *), rdh_compar_filename);

    /* Sort all children */
    for (int i = 0; i < p_node->i_children; i++)
        rdh_sort(p_node->pp_children[i]);
}