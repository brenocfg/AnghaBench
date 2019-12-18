#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct view {int curtype; int /*<<< orphan*/  win; TYPE_1__* curline; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
struct TYPE_2__ {int /*<<< orphan*/  selected; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_view_attr (struct view*,int) ; 
 int /*<<< orphan*/  get_view_color (struct view*,int) ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wchgat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
set_view_attr(struct view *view, enum line_type type)
{
	if (!view->curline->selected && view->curtype != type) {
		(void) wattrset(view->win, get_view_attr(view, type));
		wchgat(view->win, -1, 0, get_view_color(view, type), NULL);
#if defined(NCURSES_VERSION_PATCH) && NCURSES_VERSION_PATCH < 20061217
		touchwin(view->win);
#endif
		view->curtype = type;
	}
}