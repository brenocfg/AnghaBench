#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_node {struct timer_node* next; } ;
struct link_list {struct timer_node* tail; } ;

/* Variables and functions */

__attribute__((used)) static inline void
link(struct link_list *list,struct timer_node *node) {
	list->tail->next = node;
	list->tail = node;
	node->next=0;
}