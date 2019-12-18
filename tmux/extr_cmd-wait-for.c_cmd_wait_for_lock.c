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
struct wait_channel {int locked; int /*<<< orphan*/  lockers; } ;
struct cmdq_item {int /*<<< orphan*/ * client; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int CMD_RETURN_WAIT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct wait_item*,int /*<<< orphan*/ ) ; 
 struct wait_channel* cmd_wait_for_add (char const*) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*) ; 
 int /*<<< orphan*/  entry ; 
 struct wait_item* xcalloc (int,int) ; 

__attribute__((used)) static enum cmd_retval
cmd_wait_for_lock(struct cmdq_item *item, const char *name,
    struct wait_channel *wc)
{
	struct wait_item	*wi;

	if (item->client == NULL) {
		cmdq_error(item, "not able to lock");
		return (CMD_RETURN_ERROR);
	}

	if (wc == NULL)
		wc = cmd_wait_for_add(name);

	if (wc->locked) {
		wi = xcalloc(1, sizeof *wi);
		wi->item = item;
		TAILQ_INSERT_TAIL(&wc->lockers, wi, entry);
		return (CMD_RETURN_WAIT);
	}
	wc->locked = 1;

	return (CMD_RETURN_NORMAL);
}