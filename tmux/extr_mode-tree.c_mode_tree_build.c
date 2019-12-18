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
typedef  scalar_t__ uint64_t ;
struct screen {int dummy; } ;
struct mode_tree_data {size_t current; int height; int line_size; scalar_t__ preview; int /*<<< orphan*/  width; TYPE_2__* line_list; int /*<<< orphan*/  children; int /*<<< orphan*/  saved; int /*<<< orphan*/  sort_crit; int /*<<< orphan*/  modedata; int /*<<< orphan*/  (* buildcb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ;scalar_t__ no_matches; int /*<<< orphan*/ * filter; struct screen screen; } ;
struct TYPE_4__ {TYPE_1__* item; } ;
struct TYPE_3__ {scalar_t__ tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_CONCAT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  mode_tree_build_lines (struct mode_tree_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_tree_check_selected (struct mode_tree_data*) ; 
 int /*<<< orphan*/  mode_tree_clear_lines (struct mode_tree_data*) ; 
 int /*<<< orphan*/  mode_tree_free_items (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_tree_set_current (struct mode_tree_data*,scalar_t__) ; 
 int /*<<< orphan*/  screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 

void
mode_tree_build(struct mode_tree_data *mtd)
{
	struct screen	*s = &mtd->screen;
	uint64_t	 tag;

	if (mtd->line_list != NULL)
		tag = mtd->line_list[mtd->current].item->tag;
	else
		tag = UINT64_MAX;

	TAILQ_CONCAT(&mtd->saved, &mtd->children, entry);
	TAILQ_INIT(&mtd->children);

	mtd->buildcb(mtd->modedata, &mtd->sort_crit, &tag, mtd->filter);
	mtd->no_matches = TAILQ_EMPTY(&mtd->children);
	if (mtd->no_matches)
		mtd->buildcb(mtd->modedata, &mtd->sort_crit, &tag, NULL);

	mode_tree_free_items(&mtd->saved);
	TAILQ_INIT(&mtd->saved);

	mode_tree_clear_lines(mtd);
	mode_tree_build_lines(mtd, &mtd->children, 0);

	if (tag == UINT64_MAX)
		tag = mtd->line_list[mtd->current].item->tag;
	mode_tree_set_current(mtd, tag);

	mtd->width = screen_size_x(s);
	if (mtd->preview) {
		mtd->height = (screen_size_y(s) / 3) * 2;
		if (mtd->height > mtd->line_size)
			mtd->height = screen_size_y(s) / 2;
		if (mtd->height < 10)
			mtd->height = screen_size_y(s);
		if (screen_size_y(s) - mtd->height < 2)
			mtd->height = screen_size_y(s);
	} else
		mtd->height = screen_size_y(s);
	mode_tree_check_selected(mtd);
}