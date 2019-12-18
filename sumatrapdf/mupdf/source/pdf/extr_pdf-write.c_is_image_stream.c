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
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  Height ; 
 int /*<<< orphan*/  Image ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  Width ; 
 int /*<<< orphan*/  XObject ; 
 int /*<<< orphan*/  filter_implies_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_image_stream(fz_context *ctx, pdf_obj *obj)
{
	pdf_obj *o;
	if ((o = pdf_dict_get(ctx, obj, PDF_NAME(Type)), pdf_name_eq(ctx, o, PDF_NAME(XObject))))
		if ((o = pdf_dict_get(ctx, obj, PDF_NAME(Subtype)), pdf_name_eq(ctx, o, PDF_NAME(Image))))
			return 1;
	if (o = pdf_dict_get(ctx, obj, PDF_NAME(Filter)), filter_implies_image(ctx, o))
		return 1;
	if (pdf_dict_get(ctx, obj, PDF_NAME(Width)) != NULL && pdf_dict_get(ctx, obj, PDF_NAME(Height)) != NULL)
		return 1;
	return 0;
}