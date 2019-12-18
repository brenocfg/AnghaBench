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
struct TYPE_5__ {int k; float* bounds; int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * encode; } ;
struct TYPE_6__ {TYPE_1__ st; } ;
struct TYPE_7__ {float** domain; int /*<<< orphan*/  n; TYPE_2__ u; } ;
typedef  TYPE_3__ pdf_function ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fz_clamp (float,float,float) ; 
 float lerp (float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_eval_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*,int,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eval_stitching_func(fz_context *ctx, pdf_function *func, float in, float *out)
{
	float low, high;
	int k = func->u.st.k;
	float *bounds = func->u.st.bounds;
	int i;

	in = fz_clamp(in, func->domain[0][0], func->domain[0][1]);

	for (i = 0; i < k - 1; i++)
	{
		if (in < bounds[i])
			break;
	}

	if (i == 0 && k == 1)
	{
		low = func->domain[0][0];
		high = func->domain[0][1];
	}
	else if (i == 0)
	{
		low = func->domain[0][0];
		high = bounds[0];
	}
	else if (i == k - 1)
	{
		low = bounds[k - 2];
		high = func->domain[0][1];
	}
	else
	{
		low = bounds[i - 1];
		high = bounds[i];
	}

	in = lerp(in, low, high, func->u.st.encode[i * 2 + 0], func->u.st.encode[i * 2 + 1]);

	pdf_eval_function(ctx, func->u.st.funcs[i], &in, 1, out, func->n);
}