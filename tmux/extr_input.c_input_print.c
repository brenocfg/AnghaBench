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
struct screen_write_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int g0set; int g1set; TYPE_2__ cell; int /*<<< orphan*/  set; } ;
struct input_ctx {TYPE_1__ cell; int /*<<< orphan*/  ch; int /*<<< orphan*/  last; scalar_t__ utf8started; struct screen_write_ctx ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_ATTR_CHARSET ; 
 int /*<<< orphan*/  screen_write_collect_add (struct screen_write_ctx*,TYPE_2__*) ; 
 int /*<<< orphan*/  utf8_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
input_print(struct input_ctx *ictx)
{
	struct screen_write_ctx	*sctx = &ictx->ctx;
	int			 set;

	ictx->utf8started = 0; /* can't be valid UTF-8 */

	set = ictx->cell.set == 0 ? ictx->cell.g0set : ictx->cell.g1set;
	if (set == 1)
		ictx->cell.cell.attr |= GRID_ATTR_CHARSET;
	else
		ictx->cell.cell.attr &= ~GRID_ATTR_CHARSET;

	utf8_set(&ictx->cell.cell.data, ictx->ch);
	screen_write_collect_add(sctx, &ictx->cell.cell);
	ictx->last = ictx->ch;

	ictx->cell.cell.attr &= ~GRID_ATTR_CHARSET;

	return (0);
}