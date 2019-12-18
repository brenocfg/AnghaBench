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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_shade ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  CA ; 
 int /*<<< orphan*/  ExtGState ; 
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 int /*<<< orphan*/  Matrix ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PatternType ; 
 int /*<<< orphan*/  Shading ; 
 int /*<<< orphan*/  ca ; 
 int /*<<< orphan*/  fz_drop_shade_imp ; 
 int /*<<< orphan*/  fz_identity ; 
 int /*<<< orphan*/  fz_shade_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_get_matrix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_load_shading_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_store_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

fz_shade *
pdf_load_shading(fz_context *ctx, pdf_document *doc, pdf_obj *dict)
{
	fz_matrix mat;
	pdf_obj *obj;
	fz_shade *shade;

	if ((shade = pdf_find_item(ctx, fz_drop_shade_imp, dict)) != NULL)
	{
		return shade;
	}

	/* Type 2 pattern dictionary */
	if (pdf_dict_get(ctx, dict, PDF_NAME(PatternType)))
	{
		mat = pdf_dict_get_matrix(ctx, dict, PDF_NAME(Matrix));

		obj = pdf_dict_get(ctx, dict, PDF_NAME(ExtGState));
		if (obj)
		{
			if (pdf_dict_get(ctx, obj, PDF_NAME(CA)) || pdf_dict_get(ctx, obj, PDF_NAME(ca)))
			{
				fz_warn(ctx, "shading with alpha not supported");
			}
		}

		obj = pdf_dict_get(ctx, dict, PDF_NAME(Shading));
		if (!obj)
			fz_throw(ctx, FZ_ERROR_SYNTAX, "missing shading dictionary");

		shade = pdf_load_shading_dict(ctx, doc, obj, mat);
	}

	/* Naked shading dictionary */
	else
	{
		shade = pdf_load_shading_dict(ctx, doc, dict, fz_identity);
	}

	pdf_store_item(ctx, dict, shade, fz_shade_size(ctx, shade));

	return shade;
}