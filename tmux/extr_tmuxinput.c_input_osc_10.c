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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  fg; } ;
struct TYPE_4__ {TYPE_1__ gc; } ;
struct window_pane {int /*<<< orphan*/  flags; TYPE_2__ style; } ;
struct input_ctx {struct window_pane* wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  colour_join_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
input_osc_10(struct input_ctx *ictx, const char *p)
{
	struct window_pane	*wp = ictx->wp;
	u_int			 r, g, b;

	if (sscanf(p, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
	    goto bad;

	wp->style.gc.fg = colour_join_rgb(r, g, b);
	wp->flags |= PANE_REDRAW;

	return;

bad:
	log_debug("bad OSC 10: %s", p);
}