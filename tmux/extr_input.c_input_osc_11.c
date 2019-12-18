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
typedef  int /*<<< orphan*/  u_int ;
struct window_pane {int flags; int /*<<< orphan*/  options; } ;
struct input_ctx {struct window_pane* wp; } ;

/* Variables and functions */
 int PANE_REDRAW ; 
 int PANE_STYLECHANGED ; 
 int /*<<< orphan*/  input_osc_parse_colour (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int /*<<< orphan*/  options_set_style (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
input_osc_11(struct input_ctx *ictx, const char *p)
{
	struct window_pane	*wp = ictx->wp;
	u_int			 r, g, b;
	char			 tmp[16];

	if (strcmp(p, "?") == 0)
		return;

	if (!input_osc_parse_colour(p, &r, &g, &b))
	    goto bad;
	xsnprintf(tmp, sizeof tmp, "bg=#%02x%02x%02x", r, g, b);
	options_set_style(wp->options, "window-style", 1, tmp);
	options_set_style(wp->options, "window-active-style", 1, tmp);
	wp->flags |= (PANE_REDRAW|PANE_STYLECHANGED);

	return;

bad:
	log_debug("bad OSC 11: %s", p);
}