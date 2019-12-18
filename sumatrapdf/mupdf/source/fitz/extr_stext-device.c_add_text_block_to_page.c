#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_stext_page ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_STEXT_BLOCK_TEXT ; 
 TYPE_1__* add_block_to_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_stext_block *
add_text_block_to_page(fz_context *ctx, fz_stext_page *page)
{
	fz_stext_block *block = add_block_to_page(ctx, page);
	block->type = FZ_STEXT_BLOCK_TEXT;
	return block;
}