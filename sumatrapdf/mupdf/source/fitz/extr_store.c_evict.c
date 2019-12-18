#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  (* drop ) (TYPE_7__*,TYPE_10__*) ;int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ fz_store_hash ;
struct TYPE_27__ {int /*<<< orphan*/  hash; TYPE_2__* head; TYPE_1__* tail; int /*<<< orphan*/  size; } ;
typedef  TYPE_5__ fz_store ;
struct TYPE_28__ {int /*<<< orphan*/  key; TYPE_3__* type; TYPE_10__* val; TYPE_2__* next; TYPE_1__* prev; scalar_t__ size; } ;
typedef  TYPE_6__ fz_item ;
struct TYPE_29__ {TYPE_5__* store; } ;
typedef  TYPE_7__ fz_context ;
struct TYPE_25__ {int /*<<< orphan*/  (* drop_key ) (TYPE_7__*,int /*<<< orphan*/ ) ;scalar_t__ (* make_hash_key ) (TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_24__ {TYPE_1__* prev; } ;
struct TYPE_23__ {TYPE_2__* next; } ;
struct TYPE_22__ {scalar_t__ refs; int /*<<< orphan*/  (* drop ) (TYPE_7__*,TYPE_10__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_dropRef (TYPE_10__*) ; 
 int /*<<< orphan*/  fz_free (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fz_hash_remove (TYPE_7__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evict(fz_context *ctx, fz_item *item)
{
	fz_store *store = ctx->store;
	int drop;

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

	/* Drop a reference to the value (freeing if required) */
	if (item->val->refs > 0)
		(void)Memento_dropRef(item->val);
	drop = (item->val->refs > 0 && --item->val->refs == 0);

	/* Remove from the hash table */
	if (item->type->make_hash_key)
	{
		fz_store_hash hash = { NULL };
		hash.drop = item->val->drop;
		if (item->type->make_hash_key(ctx, &hash, item->key))
			fz_hash_remove(ctx, store->hash, &hash);
	}
	fz_unlock(ctx, FZ_LOCK_ALLOC);
	if (drop)
		item->val->drop(ctx, item->val);

	/* Always drops the key and drop the item */
	item->type->drop_key(ctx, item->key);
	fz_free(ctx, item);
	fz_lock(ctx, FZ_LOCK_ALLOC);
}