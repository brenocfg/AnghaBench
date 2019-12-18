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
struct TYPE_5__ {int /*<<< orphan*/  user; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ locks; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_ALLOC ; 
 int FZ_LOCK_DEBUG_CONTEXT_MAX ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_lock_times ; 
 int fz_debug_locking_inited ; 
 TYPE_2__** fz_lock_debug_contexts ; 
 int /*<<< orphan*/  fz_lock_program_start ; 
 int /*<<< orphan*/  ms_clock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_context(fz_context *ctx)
{
	int i;

	for (i = 0; i < FZ_LOCK_DEBUG_CONTEXT_MAX; i++)
	{
		if (fz_lock_debug_contexts[i] == ctx)
			return i;
		if (fz_lock_debug_contexts[i] == NULL)
		{
			int gottit = 0;
			/* We've not locked on this context before, so use
			 * this one for this new context. We might have other
			 * threads trying here too though so, so claim it
			 * atomically. No one has locked on this context
			 * before, so we are safe to take the ALLOC lock. */
			ctx->locks.lock(ctx->locks.user, FZ_LOCK_ALLOC);
			/* If it's still free, then claim it as ours,
			 * otherwise we'll keep hunting. */
			if (fz_lock_debug_contexts[i] == NULL)
			{
				gottit = 1;
				fz_lock_debug_contexts[i] = ctx;
#ifdef FITZ_DEBUG_LOCKING_TIMES
				if (fz_debug_locking_inited == 0)
				{
					fz_debug_locking_inited = 1;
					fz_lock_program_start = ms_clock();
					atexit(dump_lock_times);
				}
#endif
			}
			ctx->locks.unlock(ctx->locks.user, FZ_LOCK_ALLOC);
			if (gottit)
				return i;
		}
	}
	return -1;
}