#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ refs; int /*<<< orphan*/  (* drop ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
struct TYPE_5__ {scalar_t__ store_key_refs; TYPE_2__ storable; } ;
typedef  TYPE_1__ fz_key_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_dropRef (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

void fz_drop_key_storable_key(fz_context *ctx, const fz_key_storable *sc)
{
	/* Explicitly drop const to allow us to use const
	 * sanely throughout the code. */
	fz_key_storable *s = (fz_key_storable *)sc;
	int drop;

	if (s == NULL)
		return;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	assert(s->store_key_refs > 0 && s->storable.refs >= s->store_key_refs);
	(void)Memento_dropRef(s);
	drop = --s->storable.refs == 0;
	--s->store_key_refs;
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