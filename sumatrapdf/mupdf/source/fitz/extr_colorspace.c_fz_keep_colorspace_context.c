#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* colorspace; } ;
typedef  TYPE_1__ fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  ctx_refs; } ;
typedef  TYPE_2__ fz_colorspace_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_keep_imp (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

fz_colorspace_context *fz_keep_colorspace_context(fz_context *ctx)
{
	fz_keep_imp(ctx, ctx->colorspace, &ctx->colorspace->ctx_refs);
	return ctx->colorspace;
}