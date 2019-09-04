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
struct cmdq_list {int dummy; } ;
struct cmdq_item {struct cmdq_item* next; struct cmdq_list* queue; struct client* client; } ;
struct client {int /*<<< orphan*/  references; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (struct cmdq_list*,struct cmdq_item*,struct cmdq_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 

void
cmdq_insert_after(struct cmdq_item *after, struct cmdq_item *item)
{
	struct client		*c = after->client;
	struct cmdq_list	*queue = after->queue;
	struct cmdq_item	*next;

	do {
		next = item->next;
		item->next = NULL;

		if (c != NULL)
			c->references++;
		item->client = c;

		item->queue = queue;
		if (after->next != NULL)
			TAILQ_INSERT_AFTER(queue, after->next, item, entry);
		else
			TAILQ_INSERT_AFTER(queue, after, item, entry);
		after->next = item;

		item = next;
	} while (item != NULL);
}