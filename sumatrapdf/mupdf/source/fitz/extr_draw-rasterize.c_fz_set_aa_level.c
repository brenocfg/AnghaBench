#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  aa; } ;
typedef  TYPE_1__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_set_rasterizer_graphics_aa_level (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_set_rasterizer_text_aa_level (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void
fz_set_aa_level(fz_context *ctx, int level)
{
	fz_set_rasterizer_graphics_aa_level(ctx, &ctx->aa, level);
	fz_set_rasterizer_text_aa_level(ctx, &ctx->aa, level);
}