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
struct cmdq_item {scalar_t__ references; struct cmdq_item* name; int /*<<< orphan*/  queue; int /*<<< orphan*/ * cmdlist; int /*<<< orphan*/ * client; struct cmdq_item* shared; int /*<<< orphan*/ * formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,struct cmdq_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  format_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cmdq_item*) ; 
 int /*<<< orphan*/  server_client_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cmdq_remove(struct cmdq_item *item)
{
	if (item->shared != NULL && --item->shared->references == 0) {
		if (item->shared->formats != NULL)
			format_free(item->shared->formats);
		free(item->shared);
	}

	if (item->client != NULL)
		server_client_unref(item->client);

	if (item->cmdlist != NULL)
		cmd_list_free(item->cmdlist);

	TAILQ_REMOVE(item->queue, item, entry);

	free(item->name);
	free(item);
}