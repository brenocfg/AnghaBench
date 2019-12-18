#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t sp; TYPE_2__* stack; } ;
typedef  TYPE_3__ ps_stack ;
struct TYPE_6__ {int /*<<< orphan*/  f; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLT_MAX ; 
 int /*<<< orphan*/  PS_REAL ; 
 int /*<<< orphan*/  fz_clamp (float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (float) ; 
 int /*<<< orphan*/  ps_overflow (TYPE_3__*,int) ; 

__attribute__((used)) static void
ps_push_real(ps_stack *st, float n)
{
	if (!ps_overflow(st, 1))
	{
		st->stack[st->sp].type = PS_REAL;
		if (isnan(n))
		{
			/* Push 1.0, as it's a small known value that won't
			 * cause a divide by 0. Same reason as in fz_atof. */
			n = 1.0f;
		}
		st->stack[st->sp].u.f = fz_clamp(n, -FLT_MAX, FLT_MAX);
		st->sp++;
	}
}