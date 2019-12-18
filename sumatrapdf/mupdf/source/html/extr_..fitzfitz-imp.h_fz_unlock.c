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
struct TYPE_5__ {int /*<<< orphan*/  user; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {TYPE_1__ locks; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_lock_debug_unlock (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
fz_unlock(fz_context *ctx, int lock)
{
	fz_lock_debug_unlock(ctx, lock);
	ctx->locks.unlock(ctx->locks.user, lock);
}