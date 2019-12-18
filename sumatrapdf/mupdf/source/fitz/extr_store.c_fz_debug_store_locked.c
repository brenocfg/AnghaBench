#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  hash; TYPE_3__* head; } ;
typedef  TYPE_2__ fz_store ;
struct TYPE_15__ {TYPE_10__* val; scalar_t__ size; int /*<<< orphan*/  key; TYPE_1__* type; struct TYPE_15__* next; } ;
typedef  TYPE_3__ fz_item ;
struct TYPE_16__ {TYPE_2__* store; } ;
typedef  TYPE_4__ fz_context ;
struct TYPE_13__ {int /*<<< orphan*/  (* format_key ) (TYPE_4__*,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_dropRef (TYPE_10__*) ; 
 int /*<<< orphan*/  Memento_takeRef (TYPE_10__*) ; 
 int /*<<< orphan*/  fz_debug_store_item ; 
 int /*<<< orphan*/  fz_hash_for_each (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_lock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_debug_store_locked(fz_context *ctx)
{
	fz_item *item, *next;
	char buf[256];
	fz_store *store = ctx->store;

	printf("-- resource store contents --\n");

	for (item = store->head; item; item = next)
	{
		next = item->next;
		if (next)
		{
			(void)Memento_takeRef(next->val);
			next->val->refs++;
		}
		fz_unlock(ctx, FZ_LOCK_ALLOC);
		item->type->format_key(ctx, buf, sizeof buf, item->key);
		fz_lock(ctx, FZ_LOCK_ALLOC);
		printf("store[*][refs=%d][size=%d] key=%s val=%p\n",
				item->val->refs, (int)item->size, buf, (void *)item->val);
		if (next)
		{
			(void)Memento_dropRef(next->val);
			next->val->refs--;
		}
	}

	printf("-- resource store hash contents --\n");
	fz_hash_for_each(ctx, store->hash, NULL, fz_debug_store_item);
	printf("-- end --\n");
}