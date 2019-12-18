#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int load; int size; } ;
typedef  TYPE_1__ fz_hash_table ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* do_hash_insert (int /*<<< orphan*/ *,TYPE_1__*,void const*,void*) ; 
 int /*<<< orphan*/  fz_resize_hash (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

void *
fz_hash_insert(fz_context *ctx, fz_hash_table *table, const void *key, void *val)
{
	if (table->load > table->size * 8 / 10)
		fz_resize_hash(ctx, table, table->size * 2);
	return do_hash_insert(ctx, table, key, val);
}