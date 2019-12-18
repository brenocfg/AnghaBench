#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_function ;
struct TYPE_3__ {int** function; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_eval_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int,int*,int) ; 

__attribute__((used)) static void
pdf_sample_composite_shade_function(fz_context *ctx, fz_shade *shade, pdf_function *func, float t0, float t1)
{
	int i, n;
	float t;

	n = fz_colorspace_n(ctx, shade->colorspace);
	for (i = 0; i < 256; i++)
	{
		t = t0 + (i / 255.0f) * (t1 - t0);
		pdf_eval_function(ctx, func, &t, 1, shade->function[i], n);
		shade->function[i][n] = 1;
	}
}