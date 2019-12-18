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
struct window_pane {int dummy; } ;
struct input_ctx {struct window_pane* wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  window_pane_reset_palette (struct window_pane*) ; 
 int /*<<< orphan*/  window_pane_unset_palette (struct window_pane*,long) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
input_osc_104(struct input_ctx *ictx, const char *p)
{
	struct window_pane	*wp = ictx->wp;
	char			*copy, *s;
	long			 idx;

	if (*p == '\0') {
		window_pane_reset_palette(wp);
		return;
	}

	copy = s = xstrdup(p);
	while (*s != '\0') {
		idx = strtol(s, &s, 10);
		if (*s != '\0' && *s != ';')
			goto bad;
		if (idx < 0 || idx >= 0x100)
			goto bad;

		window_pane_unset_palette(wp, idx);
		if (*s == ';')
			s++;
	}
	free(copy);
	return;

bad:
	log_debug("bad OSC 104: %s", p);
	free(copy);
}