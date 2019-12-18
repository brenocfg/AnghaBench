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
struct TYPE_5__ {size_t sp; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ ps_stack ;

/* Variables and functions */
 int /*<<< orphan*/  ps_overflow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ps_underflow (TYPE_1__*,int) ; 

__attribute__((used)) static void
ps_index(ps_stack *st, int n)
{
	if (!ps_overflow(st, 1) && !ps_underflow(st, n + 1))
	{
		st->stack[st->sp] = st->stack[st->sp - n - 1];
		st->sp++;
	}
}