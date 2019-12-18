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
struct window {int dummy; } ;
struct layout_cell {int dummy; } ;
typedef  enum layout_type { ____Placeholder_layout_type } layout_type ;

/* Variables and functions */
 struct layout_cell* TAILQ_NEXT (struct layout_cell*,int /*<<< orphan*/ ) ; 
 struct layout_cell* TAILQ_PREV (struct layout_cell*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  layout_cells ; 
 int /*<<< orphan*/  layout_resize_adjust (struct window*,struct layout_cell*,int,int) ; 
 int layout_resize_check (struct window*,struct layout_cell*,int) ; 

__attribute__((used)) static int
layout_resize_pane_grow(struct window *w, struct layout_cell *lc,
    enum layout_type type, int needed, int opposite)
{
	struct layout_cell	*lcadd, *lcremove;
	u_int			 size = 0;

	/* Growing. Always add to the current cell. */
	lcadd = lc;

	/* Look towards the tail for a suitable cell for reduction. */
	lcremove = TAILQ_NEXT(lc, entry);
	while (lcremove != NULL) {
		size = layout_resize_check(w, lcremove, type);
		if (size > 0)
			break;
		lcremove = TAILQ_NEXT(lcremove, entry);
	}

	/* If none found, look towards the head. */
	if (opposite && lcremove == NULL) {
		lcremove = TAILQ_PREV(lc, layout_cells, entry);
		while (lcremove != NULL) {
			size = layout_resize_check(w, lcremove, type);
			if (size > 0)
				break;
			lcremove = TAILQ_PREV(lcremove, layout_cells, entry);
		}
	}
	if (lcremove == NULL)
		return (0);

	/* Change the cells. */
	if (size > (u_int) needed)
		size = needed;
	layout_resize_adjust(w, lcadd, type, size);
	layout_resize_adjust(w, lcremove, type, -size);
	return (size);
}