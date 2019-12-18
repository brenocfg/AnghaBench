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
typedef  int /*<<< orphan*/  fz_image ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XObject ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_drop_image (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_image_from_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pdf_add_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_image_res(pdf_obj *resources, char *name, char *path)
{
	fz_image *image;
	pdf_obj *subres, *ref;

	image = fz_new_image_from_file(ctx, path);

	subres = pdf_dict_get(ctx, resources, PDF_NAME(XObject));
	if (!subres)
	{
		subres = pdf_new_dict(ctx, doc, 10);
		pdf_dict_put_drop(ctx, resources, PDF_NAME(XObject), subres);
	}

	ref = pdf_add_image(ctx, doc, image);
	pdf_dict_puts(ctx, subres, name, ref);
	pdf_drop_obj(ctx, ref);

	fz_drop_image(ctx, image);
}