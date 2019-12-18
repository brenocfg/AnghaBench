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
struct TYPE_4__ {int m; int n; } ;
typedef  TYPE_1__ pdf_function ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int MAX_M ; 
 int MAX_N ; 
 int /*<<< orphan*/  pdf_eval_function_imp (int /*<<< orphan*/ *,TYPE_1__*,float const*,float*) ; 

void
pdf_eval_function(fz_context *ctx, pdf_function *func, const float *in, int inlen, float *out, int outlen)
{
	float fakein[MAX_M];
	float fakeout[MAX_N];
	int i;

	if (inlen < func->m)
	{
		for (i = 0; i < inlen; ++i)
			fakein[i] = in[i];
		for (; i < func->m; ++i)
			fakein[i] = 0;
		in = fakein;
	}

	if (outlen < func->n)
	{
		pdf_eval_function_imp(ctx, func, in, fakeout);
		for (i = 0; i < outlen; ++i)
			out[i] = fakeout[i];
	}
	else
	{
		pdf_eval_function_imp(ctx, func, in, out);
		for (i = func->n; i < outlen; ++i)
			out[i] = 0;
	}
}