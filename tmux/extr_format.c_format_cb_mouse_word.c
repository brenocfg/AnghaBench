#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  grid; } ;
struct window_pane {TYPE_1__ base; int /*<<< orphan*/  modes; } ;
struct TYPE_5__ {int /*<<< orphan*/  valid; } ;
struct format_tree {TYPE_2__ m; } ;
struct format_entry {char* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ cmd_mouse_at (struct window_pane*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct window_pane* cmd_mouse_pane (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* format_grid_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
format_cb_mouse_word(struct format_tree *ft, struct format_entry *fe)
{
	struct window_pane	*wp;
	u_int			 x, y;
	char			*s;

	if (!ft->m.valid)
		return;
	wp = cmd_mouse_pane(&ft->m, NULL, NULL);
	if (wp == NULL)
		return;
	if (!TAILQ_EMPTY (&wp->modes))
		return;
	if (cmd_mouse_at(wp, &ft->m, &x, &y, 0) != 0)
		return;

	s = format_grid_word(wp->base.grid, x, y);
	if (s != NULL)
		fe->value = s;
}