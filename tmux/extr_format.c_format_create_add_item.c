#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct window_pane {int /*<<< orphan*/  id; } ;
struct mouse_event {scalar_t__ valid; } ;
struct format_tree {int /*<<< orphan*/  m; } ;
struct cmdq_item {TYPE_3__* shared; TYPE_2__* cmd; } ;
struct TYPE_6__ {struct mouse_event mouse; int /*<<< orphan*/ * formats; } ;
struct TYPE_5__ {TYPE_1__* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ cmd_mouse_at (struct window_pane*,struct mouse_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct window_pane* cmd_mouse_pane (struct mouse_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_add_cb (struct format_tree*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_cb_mouse_line ; 
 int /*<<< orphan*/  format_cb_mouse_word ; 
 int /*<<< orphan*/  format_merge (struct format_tree*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mouse_event*,int) ; 

__attribute__((used)) static void
format_create_add_item(struct format_tree *ft, struct cmdq_item *item)
{
	struct mouse_event	*m;
	struct window_pane	*wp;
	u_int			 x, y;

	if (item->cmd != NULL)
		format_add(ft, "command", "%s", item->cmd->entry->name);

	if (item->shared == NULL)
		return;
	if (item->shared->formats != NULL)
		format_merge(ft, item->shared->formats);

	m = &item->shared->mouse;
	if (m->valid && ((wp = cmd_mouse_pane(m, NULL, NULL)) != NULL)) {
		format_add(ft, "mouse_pane", "%%%u", wp->id);
		if (cmd_mouse_at(wp, m, &x, &y, 0) == 0) {
			format_add(ft, "mouse_x", "%u", x);
			format_add(ft, "mouse_y", "%u", y);
			format_add_cb(ft, "mouse_word", format_cb_mouse_word);
			format_add_cb(ft, "mouse_line", format_cb_mouse_line);
		}
	}
	memcpy(&ft->m, m, sizeof ft->m);
}