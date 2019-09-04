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
struct cmdq_item {int /*<<< orphan*/  number; scalar_t__ time; struct client* client; } ;
struct client {int flags; int /*<<< orphan*/  stdout_data; } ;

/* Variables and functions */
 int CLIENT_CONTROL ; 
 int /*<<< orphan*/  evbuffer_add_printf (int /*<<< orphan*/ ,char*,char const*,long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_client_push_stdout (struct client*) ; 

void
cmdq_guard(struct cmdq_item *item, const char *guard, int flags)
{
	struct client	*c = item->client;

	if (c == NULL || !(c->flags & CLIENT_CONTROL))
		return;

	evbuffer_add_printf(c->stdout_data, "%%%s %ld %u %d\n", guard,
	    (long)item->time, item->number, flags);
	server_client_push_stdout(c);
}