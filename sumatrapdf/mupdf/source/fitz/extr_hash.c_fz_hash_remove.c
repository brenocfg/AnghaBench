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
struct TYPE_5__ {unsigned int size; scalar_t__ lock; int /*<<< orphan*/  keylen; TYPE_2__* ents; } ;
typedef  TYPE_1__ fz_hash_table ;
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ fz_hash_entry ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_removal (int /*<<< orphan*/ *,TYPE_1__*,void const*,unsigned int) ; 
 int /*<<< orphan*/  fz_assert_lock_held (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned int hash (void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fz_hash_remove(fz_context *ctx, fz_hash_table *table, const void *key)
{
	fz_hash_entry *ents = table->ents;
	unsigned size = table->size;
	unsigned pos = hash(key, table->keylen) % size;

	if (table->lock >= 0)
		fz_assert_lock_held(ctx, table->lock);

	while (1)
	{
		if (!ents[pos].val)
		{
			fz_warn(ctx, "assert: remove non-existent hash entry");
			return;
		}

		if (memcmp(key, ents[pos].key, table->keylen) == 0)
		{
			do_removal(ctx, table, key, pos);
			return;
		}

		pos++;
		if (pos == size)
			pos = 0;
	}
}