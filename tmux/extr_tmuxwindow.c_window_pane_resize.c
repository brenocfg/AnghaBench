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
typedef  void* u_int ;
struct window_pane {void* sx; void* sy; int /*<<< orphan*/  flags; int /*<<< orphan*/  modes; int /*<<< orphan*/ * saved_grid; int /*<<< orphan*/  base; } ;
struct window_mode_entry {TYPE_1__* mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resize ) (struct window_mode_entry*,void*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_RESIZE ; 
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_resize (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct window_mode_entry*,void*,void*) ; 

void
window_pane_resize(struct window_pane *wp, u_int sx, u_int sy)
{
	struct window_mode_entry	*wme;

	if (sx == wp->sx && sy == wp->sy)
		return;
	wp->sx = sx;
	wp->sy = sy;

	screen_resize(&wp->base, sx, sy, wp->saved_grid == NULL);

	wme = TAILQ_FIRST(&wp->modes);
	if (wme != NULL && wme->mode->resize != NULL)
		wme->mode->resize(wme, sx, sy);

	wp->flags |= PANE_RESIZE;
}