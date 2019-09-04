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
struct wait_item {struct cmdq_item* item; } ;
struct wait_channel {int /*<<< orphan*/  waiters; int /*<<< orphan*/  name; scalar_t__ woken; } ;
struct cmdq_item {struct client* client; } ;
struct client {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int CMD_RETURN_WAIT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct wait_item*,int /*<<< orphan*/ ) ; 
 struct wait_channel* cmd_wait_for_add (char const*) ; 
 int /*<<< orphan*/  cmd_wait_for_remove (struct wait_channel*) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,struct client*) ; 
 struct wait_item* xcalloc (int,int) ; 

__attribute__((used)) static enum cmd_retval
cmd_wait_for_wait(struct cmdq_item *item, const char *name,
    struct wait_channel *wc)
{
	struct client		*c = item->client;
	struct wait_item	*wi;

	if (c == NULL) {
		cmdq_error(item, "not able to wait");
		return (CMD_RETURN_ERROR);
	}

	if (wc == NULL)
		wc = cmd_wait_for_add(name);

	if (wc->woken) {
		log_debug("wait channel %s already woken (%p)", wc->name, c);
		cmd_wait_for_remove(wc);
		return (CMD_RETURN_NORMAL);
	}
	log_debug("wait channel %s not woken (%p)", wc->name, c);

	wi = xcalloc(1, sizeof *wi);
	wi->item = item;
	TAILQ_INSERT_TAIL(&wc->waiters, wi, entry);

	return (CMD_RETURN_WAIT);
}