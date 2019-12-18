#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; struct TYPE_4__* ents; int /*<<< orphan*/  (* drop_val ) (int /*<<< orphan*/ *,void*) ;void* val; } ;
typedef  TYPE_1__ fz_hash_table ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void*) ; 

void
fz_drop_hash_table(fz_context *ctx, fz_hash_table *table)
{
	if (!table)
		return;

	if (table->drop_val)
	{
		int i, n = table->size;
		for (i = 0; i < n; ++i)
		{
			void *v = table->ents[i].val;
			if (v)
				table->drop_val(ctx, v);
		}
	}

	fz_free(ctx, table->ents);
	fz_free(ctx, table);
}