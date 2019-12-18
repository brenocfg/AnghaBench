#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_8__ {int /*<<< orphan*/  resources; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ pdf_device ;
struct TYPE_9__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ gstate ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  BM ; 
 TYPE_2__* CURRENT_GSTATE (TYPE_1__*) ; 
 int /*<<< orphan*/  ExtGState ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  fz_blendmode_name (int) ; 
 int /*<<< orphan*/  fz_new_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  pdf_dev_end_text (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int pdf_dev_new_form (int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int,int,float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dev_push_new_buf (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_putp_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pdf_dev_begin_group(fz_context *ctx, fz_device *dev, fz_rect bbox, fz_colorspace *cs, int isolated, int knockout, int blendmode, float alpha)
{
	pdf_device *pdev = (pdf_device*)dev;
	pdf_document *doc = pdev->doc;
	int num;
	pdf_obj *form_ref;
	gstate *gs;

	pdf_dev_end_text(ctx, pdev);

	num = pdf_dev_new_form(ctx, &form_ref, pdev, bbox, isolated, knockout, alpha, cs);

	/* Do we have an appropriate blending extgstate already? */
	{
		char text[32];
		pdf_obj *obj;
		fz_snprintf(text, sizeof(text), "ExtGState/BlendMode%d", blendmode);
		obj = pdf_dict_getp(ctx, pdev->resources, text);
		if (obj == NULL)
		{
			/* No, better make one */
			obj = pdf_new_dict(ctx, doc, 2);
			pdf_dict_put(ctx, obj, PDF_NAME(Type), PDF_NAME(ExtGState));
			pdf_dict_put_name(ctx, obj, PDF_NAME(BM), fz_blendmode_name(blendmode));
			pdf_dict_putp_drop(ctx, pdev->resources, text, obj);
		}
	}

	/* Add the call to this group */
	gs = CURRENT_GSTATE(pdev);
	fz_append_printf(ctx, gs->buf, "/BlendMode%d gs /Fm%d Do\n", blendmode, num);

	/* Now, everything we get until the end of group needs to go into a
	 * new buffer, which will be the stream contents for the form. */
	pdf_dev_push_new_buf(ctx, pdev, fz_new_buffer(ctx, 1024), NULL, form_ref);
}