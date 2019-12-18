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
struct TYPE_4__ {struct TYPE_4__* b; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */

__attribute__((used)) static js_Ast *jsP_list(js_Ast *head)
{
	/* set parent pointers in list nodes */
	js_Ast *prev = head, *node = head->b;
	while (node) {
		node->parent = prev;
		prev = node;
		node = node->b;
	}
	return head;
}