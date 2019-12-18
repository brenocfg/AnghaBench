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
struct wait_item {int /*<<< orphan*/  item; } ;
struct wait_channel {scalar_t__ locked; int /*<<< orphan*/  lockers; } ;
struct cmdq_item {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 struct wait_item* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct wait_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_wait_for_remove (struct wait_channel*) ; 
 int /*<<< orphan*/  cmdq_continue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char const*) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct wait_item*) ; 

__attribute__((used)) static enum cmd_retval
cmd_wait_for_unlock(struct cmdq_item *item, const char *name,
    struct wait_channel *wc)
{
	struct wait_item	*wi;

	if (wc == NULL || !wc->locked) {
		cmdq_error(item, "channel %s not locked", name);
		return (CMD_RETURN_ERROR);
	}

	if ((wi = TAILQ_FIRST(&wc->lockers)) != NULL) {
		cmdq_continue(wi->item);
		TAILQ_REMOVE(&wc->lockers, wi, entry);
		free(wi);
	} else {
		wc->locked = 0;
		cmd_wait_for_remove(wc);
	}

	return (CMD_RETURN_NORMAL);
}