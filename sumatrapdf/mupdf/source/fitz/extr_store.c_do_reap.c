#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  (* drop ) (TYPE_5__*,TYPE_8__*) ;int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ fz_store_hash ;
struct TYPE_22__ {int /*<<< orphan*/  hash; TYPE_4__* head; TYPE_4__* tail; int /*<<< orphan*/  size; scalar_t__ needs_reaping; } ;
typedef  TYPE_3__ fz_store ;
struct TYPE_23__ {int /*<<< orphan*/  key; TYPE_1__* type; TYPE_8__* val; struct TYPE_23__* prev; struct TYPE_23__* next; scalar_t__ size; } ;
typedef  TYPE_4__ fz_item ;
struct TYPE_24__ {TYPE_3__* store; } ;
typedef  TYPE_5__ fz_context ;
struct TYPE_25__ {scalar_t__ refs; int /*<<< orphan*/  (* drop ) (TYPE_5__*,TYPE_8__*) ;} ;
struct TYPE_20__ {scalar_t__ (* needs_reap ) (TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* drop_key ) (TYPE_5__*,int /*<<< orphan*/ ) ;scalar_t__ (* make_hash_key ) (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_dropRef (TYPE_8__*) ; 
 int /*<<< orphan*/  fz_assert_lock_held (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fz_hash_remove (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_reap(fz_context *ctx)
{
	fz_store *store = ctx->store;
	fz_item *item, *prev, *remove;

	if (store == NULL)
	{
		fz_unlock(ctx, FZ_LOCK_ALLOC);
		return;
	}

	fz_assert_lock_held(ctx, FZ_LOCK_ALLOC);

	ctx->store->needs_reaping = 0;

	/* Reap the items */
	remove = NULL;
	for (item = store->tail; item; item = prev)
	{
		prev = item->prev;

		if (item->type->needs_reap == NULL || item->type->needs_reap(ctx, item->key) == 0)
			continue;

		/* We have to drop it */
		store->size -= item->size;

		/* Unlink from the linked list */
		if (item->next)
			item->next->prev = item->prev;
		else
			store->tail = item->prev;
		if (item->prev)
			item->prev->next = item->next;
		else
			store->head = item->next;

		/* Remove from the hash table */
		if (item->type->make_hash_key)
		{
			fz_store_hash hash = { NULL };
			hash.drop = item->val->drop;
			if (item->type->make_hash_key(ctx, &hash, item->key))
				fz_hash_remove(ctx, store->hash, &hash);
		}

		/* Store whether to drop this value or not in 'prev' */
		if (item->val->refs > 0)
			(void)Memento_dropRef(item->val);
		item->prev = (item->val->refs > 0 && --item->val->refs == 0) ? item : NULL;

		/* Store it in our removal chain - just singly linked */
		item->next = remove;
		remove = item;
	}
	fz_unlock(ctx, FZ_LOCK_ALLOC);

	/* Now drop the remove chain */
	for (item = remove; item != NULL; item = remove)
	{
		remove = item->next;

		/* Drop a reference to the value (freeing if required) */
		if (item->prev)
			item->val->drop(ctx, item->val);

		/* Always drops the key and drop the item */
		item->type->drop_key(ctx, item->key);
		fz_free(ctx, item);
	}
}