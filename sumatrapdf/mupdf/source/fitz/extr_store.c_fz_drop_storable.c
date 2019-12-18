#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int refs; int /*<<< orphan*/  (* drop ) (TYPE_3__*,TYPE_2__*) ;} ;
typedef  TYPE_2__ fz_storable ;
struct TYPE_14__ {TYPE_1__* store; } ;
typedef  TYPE_3__ fz_context ;
struct TYPE_12__ {scalar_t__ max; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 scalar_t__ FZ_STORE_UNLIMITED ; 
 int /*<<< orphan*/  Memento_dropIntRef (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scavenge (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 

void
fz_drop_storable(fz_context *ctx, const fz_storable *sc)
{
	/* Explicitly drop const to allow us to use const
	 * sanely throughout the code. */
	fz_storable *s = (fz_storable *)sc;
	int num;

	if (s == NULL)
		return;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	/* Drop the ref, and leave num as being the number of
	 * refs left (-1 meaning, "statically allocated"). */
	if (s->refs > 0)
	{
		(void)Memento_dropIntRef(s);
		num = --s->refs;
	}
	else
		num = -1;

	/* If we have just 1 ref left, it's possible that
	 * this ref is held by the store. If the store is
	 * oversized, we ought to throw any such references
	 * away to try to bring the store down to a "legal"
	 * size. Run a scavenge to check for this case. */
	if (ctx->store->max != FZ_STORE_UNLIMITED)
		if (num == 1 && ctx->store->size > ctx->store->max)
			scavenge(ctx, ctx->store->size - ctx->store->max);
	fz_unlock(ctx, FZ_LOCK_ALLOC);

	/* If we have no references to an object left, then
	 * it cannot possibly be in the store (as the store always
	 * keeps a ref to everything in it, and doesn't drop via
	 * this method). So we can simply drop the storable object
	 * itself without any operations on the fz_store.
	 */
	if (num == 0)
		s->drop(ctx, s);
}