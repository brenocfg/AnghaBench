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
typedef  int /*<<< orphan*/  ps_stack ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
struct TYPE_6__ {TYPE_1__ p; } ;
struct TYPE_7__ {int m; int n; int /*<<< orphan*/ ** range; TYPE_2__ u; int /*<<< orphan*/ ** domain; } ;
typedef  TYPE_3__ pdf_function ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fz_clamp (float const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_init_stack (int /*<<< orphan*/ *) ; 
 float ps_pop_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps_push_real (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  ps_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eval_postscript_func(fz_context *ctx, pdf_function *func, const float *in, float *out)
{
	ps_stack st;
	float x;
	int i;

	ps_init_stack(&st);

	for (i = 0; i < func->m; i++)
	{
		x = fz_clamp(in[i], func->domain[i][0], func->domain[i][1]);
		ps_push_real(&st, x);
	}

	ps_run(ctx, func->u.p.code, &st, 0);

	for (i = func->n - 1; i >= 0; i--)
	{
		x = ps_pop_real(&st);
		out[i] = fz_clamp(x, func->range[i][0], func->range[i][1]);
	}
}