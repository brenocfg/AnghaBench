#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* head; TYPE_2__* tail; } ;
typedef  TYPE_1__ fz_store ;
struct TYPE_6__ {struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_2__ fz_item ;

/* Variables and functions */

__attribute__((used)) static void
touch(fz_store *store, fz_item *item)
{
	if (item->next != item)
	{
		/* Already in the list - unlink it */
		if (item->next)
			item->next->prev = item->prev;
		else
			store->tail = item->prev;
		if (item->prev)
			item->prev->next = item->next;
		else
			store->head = item->next;
	}
	/* Now relink it at the start of the LRU chain */
	item->next = store->head;
	if (item->next)
		item->next->prev = item;
	else
		store->tail = item;
	store->head = item;
	item->prev = NULL;
}