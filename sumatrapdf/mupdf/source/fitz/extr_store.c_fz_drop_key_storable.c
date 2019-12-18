#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ refs; int /*<<< orphan*/  (* drop ) (TYPE_3__*,TYPE_5__*) ;} ;
struct TYPE_13__ {scalar_t__ store_key_refs; TYPE_5__ storable; } ;
typedef  TYPE_2__ fz_key_storable ;
struct TYPE_14__ {TYPE_1__* store; } ;
typedef  TYPE_3__ fz_context ;
struct TYPE_12__ {scalar_t__ defer_reap_count; int needs_reaping; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_dropRef (TYPE_2__*) ; 
 int /*<<< orphan*/  do_reap (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_5__*) ; 

void fz_drop_key_storable(fz_context *ctx, const fz_key_storable *sc)
{
	/* Explicitly drop const to allow us to use const
	 * sanely throughout the code. */
	fz_key_storable *s = (fz_key_storable *)sc;
	int drop;
	int unlock = 1;

	if (s == NULL)
		return;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	if (s->storable.refs > 0)
	{
		(void)Memento_dropRef(s);
		drop = --s->storable.refs == 0;
		if (!drop && s->storable.refs == s->store_key_refs)
		{
			if (ctx->store->defer_reap_count > 0)
			{
				ctx->store->needs_reaping = 1;
			}
			else
			{
				do_reap(ctx);
				unlock = 0;
			}
		}
	}
	else
		drop = 0;
	if (unlock)
		fz_unlock(ctx, FZ_LOCK_ALLOC);
	/*
		If we are dropping the last reference to an object, then
		it cannot possibly be in the store (as the store always
		keeps a ref to everything in it, and doesn't drop via
		this method. So we can simply drop the storable object
		itself without any operations on the fz_store.
	 */
	if (drop)
		s->storable.drop(ctx, &s->storable);
}