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
struct TYPE_5__ {float x; float w; char const* p; struct TYPE_5__* next; } ;
typedef  TYPE_1__ fz_layout_char ;
struct TYPE_6__ {TYPE_1__** text_tailp; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ fz_layout_block ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void fz_add_layout_char(fz_context *ctx, fz_layout_block *block, float x, float w, const char *p)
{
	fz_layout_char *ch = fz_pool_alloc(ctx, block->pool, sizeof (fz_layout_char));
	ch->x = x;
	ch->w = w;
	ch->p = p;
	ch->next = NULL;
	*block->text_tailp = ch;
	block->text_tailp = &ch->next;
}