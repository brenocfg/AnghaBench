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
struct window_pane {int dummy; } ;
struct input_ctx {struct window_pane* wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  colour_join_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_osc_parse_colour (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 char* strsep (char**,char*) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  window_pane_set_palette (struct window_pane*,long,int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
input_osc_4(struct input_ctx *ictx, const char *p)
{
	struct window_pane	*wp = ictx->wp;
	char			*copy, *s, *next = NULL;
	long	 		 idx;
	u_int			 r, g, b;

	copy = s = xstrdup(p);
	while (s != NULL && *s != '\0') {
		idx = strtol(s, &next, 10);
		if (*next++ != ';')
			goto bad;
		if (idx < 0 || idx >= 0x100)
			goto bad;

		s = strsep(&next, ";");
		if (!input_osc_parse_colour(s, &r, &g, &b)) {
			s = next;
			continue;
		}

		window_pane_set_palette(wp, idx, colour_join_rgb(r, g, b));
		s = next;
	}

	free(copy);
	return;

bad:
	log_debug("bad OSC 4: %s", p);
	free(copy);
}