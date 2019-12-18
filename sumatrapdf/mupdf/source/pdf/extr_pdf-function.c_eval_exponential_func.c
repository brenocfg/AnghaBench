#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n; float* c0; float* c1; } ;
struct TYPE_6__ {TYPE_1__ e; } ;
struct TYPE_7__ {int n; int /*<<< orphan*/ ** range; scalar_t__ has_range; TYPE_2__ u; int /*<<< orphan*/ ** domain; } ;
typedef  TYPE_3__ pdf_function ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fz_clamp (float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float powf (float,scalar_t__) ; 

__attribute__((used)) static void
eval_exponential_func(fz_context *ctx, pdf_function *func, float in, float *out)
{
	float x = in;
	float tmp;
	int i;

	x = fz_clamp(x, func->domain[0][0], func->domain[0][1]);

	/* Default output is zero, which is suitable for violated constraints */
	if ((func->u.e.n != (int)func->u.e.n && x < 0) || (func->u.e.n < 0 && x == 0))
	{
		for (i = 0; i < func->n; i++)
			out[i] = 0;
		return;
	}

	tmp = powf(x, func->u.e.n);
	for (i = 0; i < func->n; i++)
	{
		out[i] = func->u.e.c0[i] + tmp * (func->u.e.c1[i] - func->u.e.c0[i]);
		if (func->has_range)
			out[i] = fz_clamp(out[i], func->range[i][0], func->range[i][1]);
	}
}