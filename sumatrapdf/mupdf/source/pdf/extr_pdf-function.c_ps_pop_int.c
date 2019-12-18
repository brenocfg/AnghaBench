#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t sp; TYPE_2__* stack; } ;
typedef  TYPE_3__ ps_stack ;
struct TYPE_7__ {int i; int f; } ;
struct TYPE_8__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_INT ; 
 int /*<<< orphan*/  PS_REAL ; 
 scalar_t__ ps_is_type (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_underflow (TYPE_3__*,int) ; 

__attribute__((used)) static int
ps_pop_int(ps_stack *st)
{
	if (!ps_underflow(st, 1))
	{
		if (ps_is_type(st, PS_INT))
			return st->stack[--st->sp].u.i;
		if (ps_is_type(st, PS_REAL))
			return st->stack[--st->sp].u.f;
	}
	return 0;
}