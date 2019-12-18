#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int load; scalar_t__ lock; TYPE_2__* ents; } ;
typedef  TYPE_1__ fz_hash_table ;
struct TYPE_9__ {scalar_t__ val; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ fz_hash_entry ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  do_hash_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* fz_malloc_no_throw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fz_resize_hash(fz_context *ctx, fz_hash_table *table, int newsize)
{
	fz_hash_entry *oldents = table->ents;
	fz_hash_entry *newents;
	int oldsize = table->size;
	int oldload = table->load;
	int i;

	if (newsize < oldload * 8 / 10)
	{
		fz_warn(ctx, "assert: resize hash too small");
		return;
	}

	if (table->lock == FZ_LOCK_ALLOC)
		fz_unlock(ctx, table->lock);
	newents = fz_malloc_no_throw(ctx, newsize * sizeof (fz_hash_entry));
	if (table->lock == FZ_LOCK_ALLOC)
		fz_lock(ctx, table->lock);
	if (table->lock >= 0)
	{
		if (table->size >= newsize)
		{
			/* Someone else fixed it before we could lock! */
			if (table->lock == FZ_LOCK_ALLOC)
				fz_unlock(ctx, table->lock);
			fz_free(ctx, newents);
			if (table->lock == FZ_LOCK_ALLOC)
				fz_lock(ctx, table->lock);
			return;
		}
	}
	if (newents == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "hash table resize failed; out of memory (%d entries)", newsize);
	table->ents = newents;
	memset(table->ents, 0, sizeof(fz_hash_entry) * newsize);
	table->size = newsize;
	table->load = 0;

	for (i = 0; i < oldsize; i++)
	{
		if (oldents[i].val)
		{
			do_hash_insert(ctx, table, oldents[i].key, oldents[i].val);
		}
	}

	if (table->lock == FZ_LOCK_ALLOC)
		fz_unlock(ctx, table->lock);
	fz_free(ctx, oldents);
	if (table->lock == FZ_LOCK_ALLOC)
		fz_lock(ctx, table->lock);
}