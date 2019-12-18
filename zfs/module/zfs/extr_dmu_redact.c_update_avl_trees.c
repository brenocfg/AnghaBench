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
struct redact_node {TYPE_1__* rt_arg; int /*<<< orphan*/  record; } ;
typedef  int /*<<< orphan*/  avl_tree_t ;
struct TYPE_2__ {int error_code; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,struct redact_node*) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,struct redact_node*) ; 
 int /*<<< orphan*/  get_next_redact_record (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
update_avl_trees(avl_tree_t *start_tree, avl_tree_t *end_tree,
    struct redact_node *redact_node)
{
	avl_remove(start_tree, redact_node);
	avl_remove(end_tree, redact_node);
	redact_node->record = get_next_redact_record(&redact_node->rt_arg->q,
	    redact_node->record);
	avl_add(end_tree, redact_node);
	avl_add(start_tree, redact_node);
	return (redact_node->rt_arg->error_code);
}