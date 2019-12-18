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
typedef  int /*<<< orphan*/  pdf_function ;
struct TYPE_5__ {int use_function; } ;
typedef  TYPE_1__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_sample_component_shade_function (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ **,float,float) ; 
 int /*<<< orphan*/  pdf_sample_composite_shade_function (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,float,float) ; 

__attribute__((used)) static void
pdf_sample_shade_function(fz_context *ctx, fz_shade *shade, int funcs, pdf_function **func, float t0, float t1)
{
	shade->use_function = 1;
	if (funcs == 1)
		pdf_sample_composite_shade_function(ctx, shade, func[0], t0, t1);
	else
		pdf_sample_component_shade_function(ctx, shade, funcs, func, t0, t1);
}