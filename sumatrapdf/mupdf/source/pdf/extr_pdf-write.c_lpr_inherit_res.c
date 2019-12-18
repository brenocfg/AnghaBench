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
 int /*<<< orphan*/  ColorSpace ; 
 int /*<<< orphan*/  ExtGState ; 
 int /*<<< orphan*/  Font ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/  Pattern ; 
 int /*<<< orphan*/  ProcSet ; 
 int /*<<< orphan*/  Properties ; 
 int /*<<< orphan*/  Resources ; 
 int /*<<< orphan*/  Shading ; 
 int /*<<< orphan*/  XObject ; 
 int /*<<< orphan*/  lpr_inherit_res_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpr_inherit_res(fz_context *ctx, pdf_obj *node, int depth, pdf_obj *dict)
{
	while (1)
	{
		pdf_obj *o;

		node = pdf_dict_get(ctx, node, PDF_NAME(Parent));
		depth--;
		if (!node || depth < 0)
			break;

		o = pdf_dict_get(ctx, node, PDF_NAME(Resources));
		if (o)
		{
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(ExtGState));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(ColorSpace));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(Pattern));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(Shading));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(XObject));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(Font));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(ProcSet));
			lpr_inherit_res_contents(ctx, dict, o, PDF_NAME(Properties));
		}
	}
}