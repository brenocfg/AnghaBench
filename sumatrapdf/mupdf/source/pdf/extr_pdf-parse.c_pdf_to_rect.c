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
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_4__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__ fz_empty_rect ; 
 void* fz_max (float,float) ; 
 void* fz_min (float,float) ; 
 float pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_rect
pdf_to_rect(fz_context *ctx, pdf_obj *array)
{
	if (!pdf_is_array(ctx, array))
		return fz_empty_rect;
	else
	{
		float a = pdf_array_get_real(ctx, array, 0);
		float b = pdf_array_get_real(ctx, array, 1);
		float c = pdf_array_get_real(ctx, array, 2);
		float d = pdf_array_get_real(ctx, array, 3);
		fz_rect r;
		r.x0 = fz_min(a, c);
		r.y0 = fz_min(b, d);
		r.x1 = fz_max(a, c);
		r.y1 = fz_max(b, d);
		return r;
	}
}