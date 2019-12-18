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
typedef  int u_int ;
struct window_pane {int /*<<< orphan*/  event; int /*<<< orphan*/  id; struct screen* screen; } ;
struct screen {int mode; } ;
struct mouse_event {int b; char sgr_type; int sgr_b; int lb; } ;

/* Variables and functions */
 int ALL_MOUSE_MODES ; 
 int MODE_MOUSE_ALL ; 
 int MODE_MOUSE_BUTTON ; 
 int MODE_MOUSE_SGR ; 
 int MODE_MOUSE_UTF8 ; 
 int MOUSE_BUTTONS (int) ; 
 scalar_t__ MOUSE_DRAG (int) ; 
 int /*<<< orphan*/  bufferevent_write (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ cmd_mouse_at (struct window_pane*,struct mouse_event*,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ input_split2 (int,char*) ; 
 int /*<<< orphan*/  log_debug (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_pane_visible (struct window_pane*) ; 
 size_t xsnprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
input_key_mouse(struct window_pane *wp, struct mouse_event *m)
{
	struct screen	*s = wp->screen;
	int		 mode = s->mode;
	char		 buf[40];
	size_t		 len;
	u_int		 x, y;

	if ((mode & ALL_MOUSE_MODES) == 0)
		return;
	if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
		return;
	if (!window_pane_visible(wp))
		return;

	/* If this pane is not in button or all mode, discard motion events. */
	if (MOUSE_DRAG(m->b) &&
	    (mode & (MODE_MOUSE_BUTTON|MODE_MOUSE_ALL)) == 0)
	    return;

	/*
	 * If this event is a release event and not in all mode, discard it.
	 * In SGR mode we can tell absolutely because a release is normally
	 * shown by the last character. Without SGR, we check if the last
	 * buttons was also a release.
	 */
	if (m->sgr_type != ' ') {
		if (MOUSE_DRAG(m->sgr_b) &&
		    MOUSE_BUTTONS(m->sgr_b) == 3 &&
		    (~mode & MODE_MOUSE_ALL))
			return;
	} else {
		if (MOUSE_DRAG(m->b) &&
		    MOUSE_BUTTONS(m->b) == 3 &&
		    MOUSE_BUTTONS(m->lb) == 3 &&
		    (~mode & MODE_MOUSE_ALL))
			return;
	}

	/*
	 * Use the SGR (1006) extension only if the application requested it
	 * and the underlying terminal also sent the event in this format (this
	 * is because an old style mouse release event cannot be converted into
	 * the new SGR format, since the released button is unknown). Otherwise
	 * pretend that tmux doesn't speak this extension, and fall back to the
	 * UTF-8 (1005) extension if the application requested, or to the
	 * legacy format.
	 */
	if (m->sgr_type != ' ' && (s->mode & MODE_MOUSE_SGR)) {
		len = xsnprintf(buf, sizeof buf, "\033[<%u;%u;%u%c",
		    m->sgr_b, x + 1, y + 1, m->sgr_type);
	} else if (s->mode & MODE_MOUSE_UTF8) {
		if (m->b > 0x7ff - 32 || x > 0x7ff - 33 || y > 0x7ff - 33)
			return;
		len = xsnprintf(buf, sizeof buf, "\033[M");
		len += input_split2(m->b + 32, &buf[len]);
		len += input_split2(x + 33, &buf[len]);
		len += input_split2(y + 33, &buf[len]);
	} else {
		if (m->b > 223)
			return;
		len = xsnprintf(buf, sizeof buf, "\033[M");
		buf[len++] = m->b + 32;
		buf[len++] = x + 33;
		buf[len++] = y + 33;
	}
	log_debug("writing mouse %.*s to %%%u", (int)len, buf, wp->id);
	bufferevent_write(wp->event, buf, len);
}