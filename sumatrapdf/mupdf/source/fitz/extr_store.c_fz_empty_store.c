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
struct TYPE_7__ {scalar_t__ head; } ;
typedef  TYPE_1__ fz_store ;
struct TYPE_8__ {TYPE_1__* store; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  evict (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  fz_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
fz_empty_store(fz_context *ctx)
{
	fz_store *store = ctx->store;

	if (store == NULL)
		return;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	/* Run through all the items in the store */
	while (store->head)
		evict(ctx, store->head); /* Drops then retakes lock */
	fz_unlock(ctx, FZ_LOCK_ALLOC);
}