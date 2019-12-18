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
 int /*<<< orphan*/  BlackPoint ; 
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 int /*<<< orphan*/  Gamma ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhitePoint ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 float pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float pdf_to_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_load_cal_common(fz_context *ctx, pdf_obj *dict, float *wp, float *bp, float *gamma)
{
	pdf_obj *obj;
	int i;

	obj = pdf_dict_get(ctx, dict, PDF_NAME(WhitePoint));
	if (pdf_array_len(ctx, obj) != 3)
		fz_throw(ctx, FZ_ERROR_SYNTAX, "WhitePoint must be a 3-element array");

	for (i = 0; i < 3; i++)
	{
		wp[i] = pdf_array_get_real(ctx, obj, i);
		if (wp[i] < 0)
			fz_throw(ctx, FZ_ERROR_SYNTAX, "WhitePoint numbers must be positive");
	}
	if (wp[1] != 1)
		fz_throw(ctx, FZ_ERROR_SYNTAX, "WhitePoint Yw must be 1.0");

	obj = pdf_dict_get(ctx, dict, PDF_NAME(BlackPoint));
	if (pdf_array_len(ctx, obj) == 3)
	{
		for (i = 0; i < 3; i++)
		{
			bp[i] = pdf_array_get_real(ctx, obj, i);
			if (bp[i] < 0)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "BlackPoint numbers must be positive");
		}
	}

	obj = pdf_dict_get(ctx, dict, PDF_NAME(Gamma));
	if (pdf_is_number(ctx, obj))
	{
		gamma[0] = pdf_to_real(ctx, obj);
		gamma[1] = gamma[2];
		if (gamma[0] <= 0)
			fz_throw(ctx, FZ_ERROR_SYNTAX, "Gamma must be greater than zero");
	}
	else if (pdf_array_len(ctx, obj) == 3)
	{
		for (i = 0; i < 3; i++)
		{
			gamma[i] = pdf_array_get_real(ctx, obj, i);
			if (gamma[i] <= 0)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "Gamma must be greater than zero");
		}
	}
}