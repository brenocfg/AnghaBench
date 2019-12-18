#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  psobj ;
struct TYPE_4__ {int sp; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ ps_stack ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ps_underflow (TYPE_1__*,int) ; 

__attribute__((used)) static void
ps_roll(ps_stack *st, int n, int j)
{
	psobj tmp;
	int i;

	if (ps_underflow(st, n) || j == 0 || n == 0)
		return;

	if (j >= 0)
	{
		j %= n;
	}
	else
	{
		j = -j % n;
		if (j != 0)
			j = n - j;
	}

	for (i = 0; i < j; i++)
	{
		tmp = st->stack[st->sp - 1];
		memmove(st->stack + st->sp - n + 1, st->stack + st->sp - n, n * sizeof(psobj));
		st->stack[st->sp - n] = tmp;
	}
}