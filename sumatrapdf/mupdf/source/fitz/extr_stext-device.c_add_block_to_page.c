#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* last_block; TYPE_2__* first_block; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ fz_stext_page ;
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* prev; } ;
typedef  TYPE_2__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_2__* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static fz_stext_block *
add_block_to_page(fz_context *ctx, fz_stext_page *page)
{
	fz_stext_block *block = fz_pool_alloc(ctx, page->pool, sizeof *page->first_block);
	block->prev = page->last_block;
	if (!page->first_block)
		page->first_block = page->last_block = block;
	else
	{
		page->last_block->next = block;
		page->last_block = block;
	}
	return block;
}