#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* store; } ;
typedef  TYPE_1__ fz_context ;
struct TYPE_10__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_hash_table (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_drop_imp (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_empty_store (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_free (TYPE_1__*,TYPE_3__*) ; 

void
fz_drop_store_context(fz_context *ctx)
{
	if (!ctx)
		return;
	if (fz_drop_imp(ctx, ctx->store, &ctx->store->refs))
	{
		fz_empty_store(ctx);
		fz_drop_hash_table(ctx, ctx->store->hash);
		fz_free(ctx, ctx->store);
		ctx->store = NULL;
	}
}