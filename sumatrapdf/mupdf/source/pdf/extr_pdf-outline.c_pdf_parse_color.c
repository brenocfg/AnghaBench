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
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float pdf_to_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pdf_parse_color(fz_context *ctx, pdf_obj *arr, float *color)
{
	int i;
	int n;
	pdf_obj *obj;

	if (!pdf_is_array(ctx, arr))
		return 0;
	n = pdf_array_len(ctx, arr);
	if (n < 3 || n > 4) {
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		obj = pdf_array_get(ctx, arr, i);
		color[i] = pdf_to_real(ctx, obj);
	}
	return 1;
}