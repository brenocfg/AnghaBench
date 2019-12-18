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
struct cmdq_item {void* data; int /*<<< orphan*/  cb; scalar_t__ flags; scalar_t__ group; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  cmdq_cb ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_CALLBACK ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*,char const*,struct cmdq_item*) ; 
 struct cmdq_item* xcalloc (int,int) ; 

struct cmdq_item *
cmdq_get_callback1(const char *name, cmdq_cb cb, void *data)
{
	struct cmdq_item	*item;

	item = xcalloc(1, sizeof *item);
	xasprintf(&item->name, "[%s/%p]", name, item);
	item->type = CMDQ_CALLBACK;

	item->group = 0;
	item->flags = 0;

	item->cb = cb;
	item->data = data;

	return (item);
}