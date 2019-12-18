#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ fz_stext_page ;
struct TYPE_13__ {int wmode; int /*<<< orphan*/  dir; struct TYPE_13__* next; struct TYPE_13__* prev; } ;
typedef  TYPE_4__ fz_stext_line ;
struct TYPE_10__ {TYPE_4__* last_line; TYPE_4__* first_line; } ;
struct TYPE_11__ {TYPE_1__ t; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
typedef  TYPE_5__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_point ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_4__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static fz_stext_line *
add_line_to_block(fz_context *ctx, fz_stext_page *page, fz_stext_block *block, const fz_point *dir, int wmode)
{
	fz_stext_line *line = fz_pool_alloc(ctx, page->pool, sizeof *block->u.t.first_line);
	line->prev = block->u.t.last_line;
	if (!block->u.t.first_line)
		block->u.t.first_line = block->u.t.last_line = line;
	else
	{
		block->u.t.last_line->next = line;
		block->u.t.last_line = line;
	}

	line->dir = *dir;
	line->wmode = wmode;

	return line;
}