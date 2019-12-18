#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_span_mask_painter_t ;

/* Variables and functions */
 int /*<<< orphan*/ * paint_span_with_mask_0_a ; 
 int /*<<< orphan*/ * paint_span_with_mask_1 ; 
 int /*<<< orphan*/ * paint_span_with_mask_1_a ; 
 int /*<<< orphan*/ * paint_span_with_mask_3 ; 
 int /*<<< orphan*/ * paint_span_with_mask_3_a ; 
 int /*<<< orphan*/ * paint_span_with_mask_4 ; 
 int /*<<< orphan*/ * paint_span_with_mask_4_a ; 
 int /*<<< orphan*/ * paint_span_with_mask_N ; 
 int /*<<< orphan*/ * paint_span_with_mask_N_a ; 

__attribute__((used)) static fz_span_mask_painter_t *
fz_get_span_mask_painter(int a, int n)
{
	switch(n)
	{
		case 0:
			/* assert(a); */
			return paint_span_with_mask_0_a;
		case 1:
			if (a)
				return paint_span_with_mask_1_a;
			else
				return paint_span_with_mask_1;
#if FZ_PLOTTERS_RGB
		case 3:
			if (a)
				return paint_span_with_mask_3_a;
			else
				return paint_span_with_mask_3;
#endif /* FZ_PLOTTERS_RGB */
#if FZ_PLOTTERS_CMYK
		case 4:
			if (a)
				return paint_span_with_mask_4_a;
			else
				return paint_span_with_mask_4;
#endif /* FZ_PLOTTERS_CMYK */
		default:
		{
#if FZ_PLOTTERS_N
			if (a)
				return paint_span_with_mask_N_a;
			else
				return paint_span_with_mask_N;
#else
			return NULL;
#endif /* FZ_PLOTTERS_N */
		}
	}
}