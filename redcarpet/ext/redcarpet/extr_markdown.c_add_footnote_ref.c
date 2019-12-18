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
struct footnote_ref {int dummy; } ;
struct footnote_list {int /*<<< orphan*/  count; struct footnote_item* tail; struct footnote_item* head; } ;
struct footnote_item {struct footnote_item* next; struct footnote_ref* ref; } ;

/* Variables and functions */
 struct footnote_item* calloc (int,int) ; 

__attribute__((used)) static int
add_footnote_ref(struct footnote_list *list, struct footnote_ref *ref)
{
	struct footnote_item *item = calloc(1, sizeof(struct footnote_item));
	if (!item)
		return 0;
	item->ref = ref;

	if (list->head == NULL) {
		list->head = list->tail = item;
	} else {
		list->tail->next = item;
		list->tail = item;
	}
	list->count++;

	return 1;
}