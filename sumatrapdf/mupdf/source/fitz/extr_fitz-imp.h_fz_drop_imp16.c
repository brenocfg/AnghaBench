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
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int /*<<< orphan*/  Memento_checkShortPointerOrNull (scalar_t__*) ; 
 int /*<<< orphan*/  Memento_dropShortRef (void*) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
fz_drop_imp16(fz_context *ctx, void *p, int16_t *refs)
{
	if (p)
	{
		int drop;
		(void)Memento_checkShortPointerOrNull(refs);
		fz_lock(ctx, FZ_LOCK_ALLOC);
		if (*refs > 0)
		{
			(void)Memento_dropShortRef(p);
			drop = --*refs == 0;
		}
		else
			drop = 0;
		fz_unlock(ctx, FZ_LOCK_ALLOC);
		return drop;
	}
	return 0;
}