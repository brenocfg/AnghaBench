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
typedef  size_t u_int ;
struct window_pane {int /*<<< orphan*/  base; } ;
struct screen {int /*<<< orphan*/  mode; } ;
struct mode_tree_data {int references; char const** sort_list; size_t sort_size; size_t sort_type; int preview; struct screen screen; int /*<<< orphan*/  children; int /*<<< orphan*/  searchcb; int /*<<< orphan*/  drawcb; int /*<<< orphan*/  buildcb; int /*<<< orphan*/ * filter; void* modedata; struct window_pane* wp; } ;
struct args {int dummy; } ;
typedef  int /*<<< orphan*/  mode_tree_search_cb ;
typedef  int /*<<< orphan*/  mode_tree_draw_cb ;
typedef  int /*<<< orphan*/  mode_tree_build_cb ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_CURSOR ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 char* args_get (struct args*,float) ; 
 scalar_t__ args_has (struct args*,float) ; 
 int /*<<< orphan*/  screen_init (struct screen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_size_x (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_size_y (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 struct mode_tree_data* xcalloc (int,int) ; 
 int /*<<< orphan*/ * xstrdup (char*) ; 

struct mode_tree_data *
mode_tree_start(struct window_pane *wp, struct args *args,
    mode_tree_build_cb buildcb, mode_tree_draw_cb drawcb,
    mode_tree_search_cb searchcb, void *modedata, const char **sort_list,
    u_int sort_size, struct screen **s)
{
	struct mode_tree_data	*mtd;
	const char		*sort;
	u_int			 i;

	mtd = xcalloc(1, sizeof *mtd);
	mtd->references = 1;

	mtd->wp = wp;
	mtd->modedata = modedata;

	mtd->sort_list = sort_list;
	mtd->sort_size = sort_size;
	mtd->sort_type = 0;

	mtd->preview = !args_has(args, 'N');

	sort = args_get(args, 'O');
	if (sort != NULL) {
		for (i = 0; i < sort_size; i++) {
			if (strcasecmp(sort, sort_list[i]) == 0)
				mtd->sort_type = i;
		}
	}

	if (args_has(args, 'f'))
		mtd->filter = xstrdup(args_get(args, 'f'));
	else
		mtd->filter = NULL;

	mtd->buildcb = buildcb;
	mtd->drawcb = drawcb;
	mtd->searchcb = searchcb;

	TAILQ_INIT(&mtd->children);

	*s = &mtd->screen;
	screen_init(*s, screen_size_x(&wp->base), screen_size_y(&wp->base), 0);
	(*s)->mode &= ~MODE_CURSOR;

	return (mtd);
}