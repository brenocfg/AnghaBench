#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fz_store_scavenge (int /*<<< orphan*/ *,size_t,int*) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int fz_store_scavenge_external(fz_context *ctx, size_t size, int *phase)
{
	int ret;

	fz_lock(ctx, FZ_LOCK_ALLOC);
	ret = fz_store_scavenge(ctx, size, phase);
	fz_unlock(ctx, FZ_LOCK_ALLOC);

	return ret;
}