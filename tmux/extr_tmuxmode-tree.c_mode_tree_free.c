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
struct window_pane {int /*<<< orphan*/  window; } ;
struct mode_tree_data {scalar_t__ zoomed; int dead; int /*<<< orphan*/  filter; int /*<<< orphan*/  search; int /*<<< orphan*/  screen; int /*<<< orphan*/  children; struct window_pane* wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_tree_clear_lines (struct mode_tree_data*) ; 
 int /*<<< orphan*/  mode_tree_free_items (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_tree_remove_ref (struct mode_tree_data*) ; 
 int /*<<< orphan*/  screen_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_unzoom_window (int /*<<< orphan*/ ) ; 

void
mode_tree_free(struct mode_tree_data *mtd)
{
	struct window_pane	*wp = mtd->wp;

	if (mtd->zoomed == 0)
		server_unzoom_window(wp->window);

	mode_tree_free_items(&mtd->children);
	mode_tree_clear_lines(mtd);
	screen_free(&mtd->screen);

	free(mtd->search);
	free(mtd->filter);

	mtd->dead = 1;
	mode_tree_remove_ref(mtd);
}