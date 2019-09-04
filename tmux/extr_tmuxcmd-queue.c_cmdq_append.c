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
struct cmdq_item {struct cmdq_list* queue; struct client* client; struct cmdq_item* next; } ;
struct client {int /*<<< orphan*/  references; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct cmdq_list*,struct cmdq_item*,int /*<<< orphan*/ ) ; 
 struct cmdq_list* cmdq_get (struct client*) ; 
 int /*<<< orphan*/  entry ; 

void
cmdq_append(struct client *c, struct cmdq_item *item)
{
	struct cmdq_list	*queue = cmdq_get(c);
	struct cmdq_item	*next;

	do {
		next = item->next;
		item->next = NULL;

		if (c != NULL)
			c->references++;
		item->client = c;

		item->queue = queue;
		TAILQ_INSERT_TAIL(queue, item, entry);

		item = next;
	} while (item != NULL);
}