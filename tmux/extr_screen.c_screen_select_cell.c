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
struct screen {TYPE_1__* sel; } ;
struct grid_cell {int attr; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  cell; scalar_t__ hidden; } ;

/* Variables and functions */
 int GRID_ATTR_CHARSET ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  utf8_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
screen_select_cell(struct screen *s, struct grid_cell *dst,
    const struct grid_cell *src)
{
	if (s->sel == NULL || s->sel->hidden)
		return;

	memcpy(dst, &s->sel->cell, sizeof *dst);

	utf8_copy(&dst->data, &src->data);
	dst->attr = dst->attr & ~GRID_ATTR_CHARSET;
	dst->attr |= src->attr & GRID_ATTR_CHARSET;
	dst->flags = src->flags;
}