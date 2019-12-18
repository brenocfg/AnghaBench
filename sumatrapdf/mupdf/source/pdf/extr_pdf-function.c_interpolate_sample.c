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
struct TYPE_5__ {float* samples; } ;
struct TYPE_6__ {TYPE_1__ sa; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ pdf_function ;

/* Variables and functions */

__attribute__((used)) static float
interpolate_sample(pdf_function *func, int *scale, int *e0, int *e1, float *efrac, int dim, int idx)
{
	float a, b;
	int idx0, idx1;

	idx0 = e0[dim] * scale[dim] + idx;
	idx1 = e1[dim] * scale[dim] + idx;

	if (dim == 0)
	{
		a = func->u.sa.samples[idx0];
		b = func->u.sa.samples[idx1];
	}
	else
	{
		a = interpolate_sample(func, scale, e0, e1, efrac, dim - 1, idx0);
		b = interpolate_sample(func, scale, e0, e1, efrac, dim - 1, idx1);
	}

	return a + (b - a) * efrac[dim];
}