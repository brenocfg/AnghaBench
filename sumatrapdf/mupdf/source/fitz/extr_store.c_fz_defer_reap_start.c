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
struct TYPE_7__ {TYPE_1__* store; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_6__ {int /*<<< orphan*/  defer_reap_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  fz_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 

void fz_defer_reap_start(fz_context *ctx)
{
	if (ctx->store == NULL)
		return;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	ctx->store->defer_reap_count++;
	fz_unlock(ctx, FZ_LOCK_ALLOC);
}