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
typedef  int u_int ;
struct window_pane {TYPE_2__* window; } ;
struct screen_write_ctx {int dummy; } ;
struct screen {int dummy; } ;
struct options {int dummy; } ;
struct mode_tree_line {int depth; struct mode_tree_item* item; scalar_t__ last; scalar_t__ flat; } ;
struct mode_tree_item {int /*<<< orphan*/  itemdata; int /*<<< orphan*/  name; scalar_t__ tagged; int /*<<< orphan*/  text; TYPE_3__* parent; scalar_t__ expanded; int /*<<< orphan*/  children; } ;
struct TYPE_4__ {size_t field; scalar_t__ reversed; } ;
struct mode_tree_data {scalar_t__ line_size; int width; int height; int offset; int current; int /*<<< orphan*/  modedata; int /*<<< orphan*/  (* drawcb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct screen_write_ctx*,int,int) ;scalar_t__ no_matches; int /*<<< orphan*/ * filter; TYPE_1__ sort_crit; int /*<<< orphan*/ * sort_list; struct mode_tree_line* line_list; int /*<<< orphan*/  preview; struct screen screen; struct window_pane* wp; } ;
struct grid_cell {int bg; int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {size_t line; } ;
struct TYPE_5__ {struct options* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_ATTR_BRIGHT ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_draw (struct screen_write_ctx*,struct grid_cell*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_box (struct screen_write_ctx*,int,int) ; 
 int /*<<< orphan*/  screen_write_clearendofline (struct screen_write_ctx*,int) ; 
 int /*<<< orphan*/  screen_write_clearscreen (struct screen_write_ctx*,int) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_puts (struct screen_write_ctx*,struct grid_cell*,char*,...) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,int /*<<< orphan*/ *,struct screen*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct screen_write_ctx*,int,int) ; 
 int /*<<< orphan*/  style_apply (struct grid_cell*,struct options*,char*) ; 
 int utf8_cstrwidth (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int,char*,char*,...) ; 
 char* xcalloc (int,size_t) ; 
 char* xstrdup (char const*) ; 

void
mode_tree_draw(struct mode_tree_data *mtd)
{
	struct window_pane	*wp = mtd->wp;
	struct screen		*s = &mtd->screen;
	struct mode_tree_line	*line;
	struct mode_tree_item	*mti;
	struct options		*oo = wp->window->options;
	struct screen_write_ctx	 ctx;
	struct grid_cell	 gc0, gc;
	u_int			 w, h, i, j, sy, box_x, box_y, width;
	char			*text, *start, key[7];
	const char		*tag, *symbol;
	size_t			 size, n;
	int			 keylen;

	if (mtd->line_size == 0)
		return;

	memcpy(&gc0, &grid_default_cell, sizeof gc0);
	memcpy(&gc, &grid_default_cell, sizeof gc);
	style_apply(&gc, oo, "mode-style");

	w = mtd->width;
	h = mtd->height;

	screen_write_start(&ctx, NULL, s);
	screen_write_clearscreen(&ctx, 8);

	if (mtd->line_size > 10)
		keylen = 6;
	else
		keylen = 4;

	for (i = 0; i < mtd->line_size; i++) {
		if (i < mtd->offset)
			continue;
		if (i > mtd->offset + h - 1)
			break;

		line = &mtd->line_list[i];
		mti = line->item;

		screen_write_cursormove(&ctx, 0, i - mtd->offset, 0);

		if (i < 10)
			snprintf(key, sizeof key, "(%c)  ", '0' + i);
		else if (i < 36)
			snprintf(key, sizeof key, "(M-%c)", 'a' + (i - 10));
		else
			*key = '\0';

		if (line->flat)
			symbol = "";
		else if (TAILQ_EMPTY(&mti->children))
			symbol = "  ";
		else if (mti->expanded)
			symbol = "- ";
		else
			symbol = "+ ";

		if (line->depth == 0)
			start = xstrdup(symbol);
		else {
			size = (4 * line->depth) + 32;

			start = xcalloc(1, size);
			for (j = 1; j < line->depth; j++) {
				if (mti->parent != NULL &&
				    mtd->line_list[mti->parent->line].last)
					strlcat(start, "    ", size);
				else
					strlcat(start, "\001x\001   ", size);
			}
			if (line->last)
				strlcat(start, "\001mq\001> ", size);
			else
				strlcat(start, "\001tq\001> ", size);
			strlcat(start, symbol, size);
		}

		if (mti->tagged)
			tag = "*";
		else
			tag = "";
		xasprintf(&text, "%-*s%s%s%s: ", keylen, key, start, mti->name,
		    tag);
		width = utf8_cstrwidth(text);
		free(start);

		if (mti->tagged) {
			gc.attr ^= GRID_ATTR_BRIGHT;
			gc0.attr ^= GRID_ATTR_BRIGHT;
		}

		if (i != mtd->current) {
			screen_write_clearendofline(&ctx, 8);
			screen_write_puts(&ctx, &gc0, "%s", text);
			format_draw(&ctx, &gc0, w - width, mti->text, NULL);
		} else {
			screen_write_clearendofline(&ctx, gc.bg);
			screen_write_puts(&ctx, &gc, "%s", text);
			format_draw(&ctx, &gc, w - width, mti->text, NULL);
		}
		free(text);

		if (mti->tagged) {
			gc.attr ^= GRID_ATTR_BRIGHT;
			gc0.attr ^= GRID_ATTR_BRIGHT;
		}
	}

	sy = screen_size_y(s);
	if (!mtd->preview || sy <= 4 || h <= 4 || sy - h <= 4 || w <= 4) {
		screen_write_stop(&ctx);
		return;
	}

	line = &mtd->line_list[mtd->current];
	mti = line->item;

	screen_write_cursormove(&ctx, 0, h, 0);
	screen_write_box(&ctx, w, sy - h);

	xasprintf(&text, " %s (sort: %s%s)", mti->name,
	    mtd->sort_list[mtd->sort_crit.field],
	    mtd->sort_crit.reversed ? ", reversed" : "");
	if (w - 2 >= strlen(text)) {
		screen_write_cursormove(&ctx, 1, h, 0);
		screen_write_puts(&ctx, &gc0, "%s", text);

		if (mtd->no_matches)
			n = (sizeof "no matches") - 1;
		else
			n = (sizeof "active") - 1;
		if (mtd->filter != NULL && w - 2 >= strlen(text) + 10 + n + 2) {
			screen_write_puts(&ctx, &gc0, " (filter: ");
			if (mtd->no_matches)
				screen_write_puts(&ctx, &gc, "no matches");
			else
				screen_write_puts(&ctx, &gc0, "active");
			screen_write_puts(&ctx, &gc0, ") ");
		}
	}
	free(text);

	box_x = w - 4;
	box_y = sy - h - 2;

	if (box_x != 0 && box_y != 0) {
		screen_write_cursormove(&ctx, 2, h + 1, 0);
		mtd->drawcb(mtd->modedata, mti->itemdata, &ctx, box_x, box_y);
	}

	screen_write_stop(&ctx);
}