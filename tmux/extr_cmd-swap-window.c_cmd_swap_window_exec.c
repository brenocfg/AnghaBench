#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct winlink {int /*<<< orphan*/  idx; struct window* window; } ;
struct window {int /*<<< orphan*/  winlinks; } ;
struct session_group {int dummy; } ;
struct session {int dummy; } ;
struct TYPE_4__ {struct session* s; struct winlink* wl; } ;
struct TYPE_3__ {struct session* s; struct winlink* wl; } ;
struct cmdq_item {TYPE_2__ target; TYPE_1__ source; } ;
struct cmd {int /*<<< orphan*/  args; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct winlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct winlink*,int /*<<< orphan*/ ) ; 
 scalar_t__ args_has (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*) ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 int /*<<< orphan*/  server_redraw_session_group (struct session*) ; 
 struct session_group* session_group_contains (struct session*) ; 
 int /*<<< orphan*/  session_group_synchronize_from (struct session*) ; 
 int /*<<< orphan*/  session_select (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wentry ; 

__attribute__((used)) static enum cmd_retval
cmd_swap_window_exec(struct cmd *self, struct cmdq_item *item)
{
	struct session		*src, *dst;
	struct session_group	*sg_src, *sg_dst;
	struct winlink		*wl_src, *wl_dst;
	struct window		*w_src, *w_dst;

	wl_src = item->source.wl;
	src = item->source.s;
	sg_src = session_group_contains(src);

	wl_dst = item->target.wl;
	dst = item->target.s;
	sg_dst = session_group_contains(dst);

	if (src != dst && sg_src != NULL && sg_dst != NULL &&
	    sg_src == sg_dst) {
		cmdq_error(item, "can't move window, sessions are grouped");
		return (CMD_RETURN_ERROR);
	}

	if (wl_dst->window == wl_src->window)
		return (CMD_RETURN_NORMAL);

	w_dst = wl_dst->window;
	TAILQ_REMOVE(&w_dst->winlinks, wl_dst, wentry);
	w_src = wl_src->window;
	TAILQ_REMOVE(&w_src->winlinks, wl_src, wentry);

	wl_dst->window = w_src;
	TAILQ_INSERT_TAIL(&w_src->winlinks, wl_dst, wentry);
	wl_src->window = w_dst;
	TAILQ_INSERT_TAIL(&w_dst->winlinks, wl_src, wentry);

	if (args_has(self->args, 'd')) {
		session_select(dst, wl_dst->idx);
		if (src != dst)
			session_select(src, wl_src->idx);
	}
	session_group_synchronize_from(src);
	server_redraw_session_group(src);
	if (src != dst) {
		session_group_synchronize_from(dst);
		server_redraw_session_group(dst);
	}
	recalculate_sizes();

	return (CMD_RETURN_NORMAL);
}