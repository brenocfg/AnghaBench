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
typedef  int /*<<< orphan*/  uint8_t ;
struct footnote_ref {unsigned int id; } ;
struct footnote_list {struct footnote_item* head; } ;
struct footnote_item {struct footnote_item* next; struct footnote_ref* ref; } ;

/* Variables and functions */
 unsigned int hash_link_ref (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct footnote_ref *
find_footnote_ref(struct footnote_list *list, uint8_t *name, size_t length)
{
	unsigned int hash = hash_link_ref(name, length);
	struct footnote_item *item = NULL;

	item = list->head;

	while (item != NULL) {
		if (item->ref->id == hash)
			return item->ref;
		item = item->next;
	}

	return NULL;
}