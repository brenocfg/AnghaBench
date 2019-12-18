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
struct TYPE_22__ {int /*<<< orphan*/  hash; TYPE_4__* head; TYPE_4__* tail; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ fz_store ;
struct TYPE_23__ {int /*<<< orphan*/  key; TYPE_1__* type; TYPE_8__* val; struct TYPE_23__* next; scalar_t__ size; struct TYPE_23__* prev; } ;
typedef  TYPE_4__ fz_item ;
struct TYPE_24__ {TYPE_3__* store; } ;
typedef  TYPE_5__ fz_context ;
struct TYPE_25__ {int refs; int /*<<< orphan*/  (* drop ) (TYPE_5__*,TYPE_8__*) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  (* drop_key ) (TYPE_5__*,int /*<<< orphan*/ ) ;scalar_t__ (* make_hash_key ) (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_dropRef (TYPE_8__*) ; 
 int /*<<< orphan*/  fz_assert_lock_held (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fz_hash_remove (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
ensure_space(fz_context *ctx, size_t tofree)
{
	fz_item *item, *prev;
	size_t count;
	fz_store *store = ctx->store;
	fz_item *to_be_freed = NULL;

	fz_assert_lock_held(ctx, FZ_LOCK_ALLOC);

	/* First check that we *can* free tofree; if not, we'd rather not
	 * cache this. */
	count = 0;
	for (item = store->tail; item; item = item->prev)
	{
		if (item->val->refs == 1)
		{
			count += item->size;
			if (count >= tofree)
				break;
		}
	}

	/* If we ran out of items to search, then we can never free enough */
	if (item == NULL)
	{
		return 0;
	}

	/* Now move all the items to be freed onto 'to_be_freed' */
	count = 0;
	for (item = store->tail; item; item = prev)
	{
		prev = item->prev;
		if (item->val->refs != 1)
			continue;

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

		/* Link into to_be_freed */
		item->next = to_be_freed;
		to_be_freed = item;

		count += item->size;
		if (count >= tofree)
			break;
	}

	/* Now we can safely drop the lock and free our pending items. These
	 * have all been removed from both the store list, and the hash table,
	 * so they can't be 'found' by anyone else in the meantime. */

	while (to_be_freed)
	{
		fz_item *item = to_be_freed;
		int drop;

		to_be_freed = to_be_freed->next;

		/* Drop a reference to the value (freeing if required) */
		if (item->val->refs > 0)
			(void)Memento_dropRef(item->val);
		drop = (item->val->refs > 0 && --item->val->refs == 0);

		fz_unlock(ctx, FZ_LOCK_ALLOC);
		if (drop)
			item->val->drop(ctx, item->val);

		/* Always drops the key and drop the item */
		item->type->drop_key(ctx, item->key);
		fz_free(ctx, item);
		fz_lock(ctx, FZ_LOCK_ALLOC);
	}

	return count;
}