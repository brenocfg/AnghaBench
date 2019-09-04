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
typedef  int u_int ;
typedef  int /*<<< orphan*/  time_t ;
struct window_pane {TYPE_1__* window; } ;
struct window_mode_entry {struct window_clock_mode_data* data; struct window_pane* wp; } ;
struct screen {int dummy; } ;
struct window_clock_mode_data {struct screen screen; } ;
struct tm {int tm_hour; } ;
struct screen_write_ctx {int dummy; } ;
struct grid_cell {int fg; int bg; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_FLAG_NOPALETTE ; 
 int /*<<< orphan*/  grid_default_cell ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int options_get_number (int /*<<< orphan*/ ,char*) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_clearscreen (struct screen_write_ctx*,int) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_putc (struct screen_write_ctx*,struct grid_cell*,char) ; 
 int /*<<< orphan*/  screen_write_puts (struct screen_write_ctx*,struct grid_cell*,char*,char*) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,int /*<<< orphan*/ *,struct screen*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__*** window_clock_table ; 

__attribute__((used)) static void
window_clock_draw_screen(struct window_mode_entry *wme)
{
	struct window_pane		*wp = wme->wp;
	struct window_clock_mode_data	*data = wme->data;
	struct screen_write_ctx	 	 ctx;
	int				 colour, style;
	struct screen			*s = &data->screen;
	struct grid_cell		 gc;
	char				 tim[64], *ptr;
	time_t				 t;
	struct tm			*tm;
	u_int				 i, j, x, y, idx;

	colour = options_get_number(wp->window->options, "clock-mode-colour");
	style = options_get_number(wp->window->options, "clock-mode-style");

	screen_write_start(&ctx, NULL, s);

	t = time(NULL);
	tm = localtime(&t);
	if (style == 0) {
		strftime(tim, sizeof tim, "%l:%M ", localtime(&t));
		if (tm->tm_hour >= 12)
			strlcat(tim, "PM", sizeof tim);
		else
			strlcat(tim, "AM", sizeof tim);
	} else
		strftime(tim, sizeof tim, "%H:%M", tm);

	screen_write_clearscreen(&ctx, 8);

	if (screen_size_x(s) < 6 * strlen(tim) || screen_size_y(s) < 6) {
		if (screen_size_x(s) >= strlen(tim) && screen_size_y(s) != 0) {
			x = (screen_size_x(s) / 2) - (strlen(tim) / 2);
			y = screen_size_y(s) / 2;
			screen_write_cursormove(&ctx, x, y, 0);

			memcpy(&gc, &grid_default_cell, sizeof gc);
			gc.flags |= GRID_FLAG_NOPALETTE;
			gc.fg = colour;
			screen_write_puts(&ctx, &gc, "%s", tim);
		}

		screen_write_stop(&ctx);
		return;
	}

	x = (screen_size_x(s) / 2) - 3 * strlen(tim);
	y = (screen_size_y(s) / 2) - 3;

	memcpy(&gc, &grid_default_cell, sizeof gc);
	gc.flags |= GRID_FLAG_NOPALETTE;
	gc.bg = colour;
	for (ptr = tim; *ptr != '\0'; ptr++) {
		if (*ptr >= '0' && *ptr <= '9')
			idx = *ptr - '0';
		else if (*ptr == ':')
			idx = 10;
		else if (*ptr == 'A')
			idx = 11;
		else if (*ptr == 'P')
			idx = 12;
		else if (*ptr == 'M')
			idx = 13;
		else {
			x += 6;
			continue;
		}

		for (j = 0; j < 5; j++) {
			for (i = 0; i < 5; i++) {
				screen_write_cursormove(&ctx, x + i, y + j, 0);
				if (window_clock_table[idx][j][i])
					screen_write_putc(&ctx, &gc, ' ');
			}
		}
		x += 6;
	}

	screen_write_stop(&ctx);
}