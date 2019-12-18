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
 int /*<<< orphan*/  Memento_checkIntPointerOrNull (int*) ; 
 int /*<<< orphan*/  Memento_takeRef (void*) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *
fz_keep_imp(fz_context *ctx, void *p, int *refs)
{
	if (p)
	{
		(void)Memento_checkIntPointerOrNull(refs);
		fz_lock(ctx, FZ_LOCK_ALLOC);
		if (*refs > 0)
		{
			(void)Memento_takeRef(p);
			++*refs;
		}
		fz_unlock(ctx, FZ_LOCK_ALLOC);
	}
	return p;
}