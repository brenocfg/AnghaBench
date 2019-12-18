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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_min (int,float) ; 
 int /*<<< orphan*/  pdf_annot_color_imp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,float*) ; 

__attribute__((used)) static int pdf_annot_color_rgb(fz_context *ctx, pdf_obj *arr, float rgb[3])
{
	float color[4];
	int n;
	pdf_annot_color_imp(ctx, arr, &n, color);
	if (n == 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		rgb[0] = rgb[1] = rgb[2] = color[0];
	}
	else if (n == 3)
	{
		rgb[0] = color[0];
		rgb[1] = color[1];
		rgb[2] = color[2];
	}
	else if (n == 4)
	{
		rgb[0] = 1 - fz_min(1, color[0] + color[3]);
		rgb[1] = 1 - fz_min(1, color[1] + color[3]);
		rgb[2] = 1 - fz_min(1, color[2] + color[3]);
	}
	return 1;
}