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
struct TYPE_2__ {int fg; int bg; int /*<<< orphan*/  attr; } ;
struct style {TYPE_1__ gc; } ;
struct options {int dummy; } ;
struct grid_cell {int fg; int bg; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 struct style* options_get_style (struct options*,char const*) ; 

void
style_apply_update(struct grid_cell *gc, struct options *oo, const char *name)
{
	struct style	*sy;

	sy = options_get_style(oo, name);
	if (sy->gc.fg != 8)
		gc->fg = sy->gc.fg;
	if (sy->gc.bg != 8)
		gc->bg = sy->gc.bg;
	if (sy->gc.attr != 0)
		gc->attr |= sy->gc.attr;
}