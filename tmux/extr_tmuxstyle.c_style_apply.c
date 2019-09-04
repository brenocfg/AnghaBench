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
struct TYPE_2__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
struct style {TYPE_1__ gc; } ;
struct options {int dummy; } ;
struct grid_cell {int /*<<< orphan*/  attr; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 struct style* options_get_style (struct options*,char const*) ; 

void
style_apply(struct grid_cell *gc, struct options *oo, const char *name)
{
	struct style	*sy;

	memcpy(gc, &grid_default_cell, sizeof *gc);
	sy = options_get_style(oo, name);
	gc->fg = sy->gc.fg;
	gc->bg = sy->gc.bg;
	gc->attr |= sy->gc.attr;
}