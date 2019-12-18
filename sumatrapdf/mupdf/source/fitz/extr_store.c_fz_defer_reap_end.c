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
struct TYPE_8__ {TYPE_1__* store; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_7__ {scalar_t__ defer_reap_count; scalar_t__ needs_reaping; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  do_reap (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 

void fz_defer_reap_end(fz_context *ctx)
{
	int reap;

	if (ctx->store == NULL)
		return;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	--ctx->store->defer_reap_count;
	reap = ctx->store->defer_reap_count == 0 && ctx->store->needs_reaping;
	if (reap)
		do_reap(ctx); /* Drops FZ_LOCK_ALLOC */
	else
		fz_unlock(ctx, FZ_LOCK_ALLOC);
}