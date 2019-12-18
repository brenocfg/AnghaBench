#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; int max; } ;
typedef  TYPE_1__ fz_store ;
struct TYPE_10__ {TYPE_1__* store; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int FZ_STORE_UNLIMITED ; 
 int /*<<< orphan*/  Memento_listBlocks () ; 
 int /*<<< orphan*/  Memento_stats () ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  fz_debug_store (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_debug_store_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_stdout (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_write_printf (TYPE_2__*,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ scavenge (TYPE_2__*,size_t) ; 

int fz_store_scavenge(fz_context *ctx, size_t size, int *phase)
{
	fz_store *store;
	size_t max;

	store = ctx->store;
	if (store == NULL)
		return 0;

#ifdef DEBUG_SCAVENGING
	fz_write_printf(ctx, fz_stdout(ctx), "Scavenging: store=%zu size=%zu phase=%d\n", store->size, size, *phase);
	fz_debug_store_locked(ctx);
	Memento_stats();
#endif
	do
	{
		size_t tofree;

		/* Calculate 'max' as the maximum size of the store for this phase */
		if (*phase >= 16)
			max = 0;
		else if (store->max != FZ_STORE_UNLIMITED)
			max = store->max / 16 * (16 - *phase);
		else
			max = store->size / (16 - *phase) * (15 - *phase);
		(*phase)++;

		/* Slightly baroque calculations to avoid overflow */
		if (size > SIZE_MAX - store->size)
			tofree = SIZE_MAX - max;
		else if (size + store->size > max)
			continue;
		else
			tofree = size + store->size - max;

		if (scavenge(ctx, tofree))
		{
#ifdef DEBUG_SCAVENGING
			fz_write_printf(ctx, fz_stdout(ctx), "scavenged: store=%zu\n", store->size);
			fz_debug_store(ctx);
			Memento_stats();
#endif
			return 1;
		}
	}
	while (max > 0);

#ifdef DEBUG_SCAVENGING
	printf("scavenging failed\n");
	fz_debug_store(ctx);
	Memento_listBlocks();
#endif
	return 0;
}