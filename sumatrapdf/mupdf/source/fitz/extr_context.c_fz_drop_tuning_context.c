#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* tuning; } ;
typedef  TYPE_1__ fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static void fz_drop_tuning_context(fz_context *ctx)
{
	if (!ctx)
		return;
	if (fz_drop_imp(ctx, ctx->tuning, &ctx->tuning->refs))
	{
		fz_free(ctx, ctx->tuning);
	}
}