#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float x; float y; float h; char const* p; int /*<<< orphan*/ * text; struct TYPE_5__* next; } ;
typedef  TYPE_1__ fz_layout_line ;
struct TYPE_6__ {int /*<<< orphan*/ ** text_tailp; TYPE_1__** tailp; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ fz_layout_block ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void fz_add_layout_line(fz_context *ctx, fz_layout_block *block, float x, float y, float h, const char *p)
{
	fz_layout_line *line = fz_pool_alloc(ctx, block->pool, sizeof (fz_layout_line));
	line->x = x;
	line->y = y;
	line->h = h;
	line->p = p;
	line->text = NULL;
	line->next = NULL;
	*block->tailp = line;
	block->tailp = &line->next;
	block->text_tailp = &line->text;
}