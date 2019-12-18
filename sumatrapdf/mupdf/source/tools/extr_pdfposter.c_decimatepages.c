#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_9__ {float x1; float x0; float y1; float y0; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  ArtBox ; 
 int /*<<< orphan*/  BleedBox ; 
 int /*<<< orphan*/  Count ; 
 int /*<<< orphan*/  CropBox ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  MediaBox ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pages ; 
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  Rotate ; 
 int /*<<< orphan*/  TrimBox ; 
 int /*<<< orphan*/  Type ; 
 TYPE_1__ fz_intersect_rect (TYPE_1__,TYPE_1__) ; 
 scalar_t__ fz_is_empty_rect (TYPE_1__) ; 
 TYPE_1__ fz_make_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  intersect_box (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/ * pdf_add_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_push_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_push_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/ * pdf_copy_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_flatten_inheritable_page_items (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_lookup_page_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ pdf_to_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_update_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int x_factor ; 
 int y_factor ; 

__attribute__((used)) static void decimatepages(fz_context *ctx, pdf_document *doc)
{
	pdf_obj *oldroot, *root, *pages, *kids;
	int num_pages = pdf_count_pages(ctx, doc);
	int page, kidcount;
	fz_rect mediabox, cropbox;
	int rotate;

	oldroot = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Root));
	pages = pdf_dict_get(ctx, oldroot, PDF_NAME(Pages));

	root = pdf_new_dict(ctx, doc, 2);
	pdf_dict_put(ctx, root, PDF_NAME(Type), pdf_dict_get(ctx, oldroot, PDF_NAME(Type)));
	pdf_dict_put(ctx, root, PDF_NAME(Pages), pdf_dict_get(ctx, oldroot, PDF_NAME(Pages)));

	pdf_update_object(ctx, doc, pdf_to_num(ctx, oldroot), root);

	pdf_drop_obj(ctx, root);

	/* Create a new kids array with our new pages in */
	kids = pdf_new_array(ctx, doc, 1);

	kidcount = 0;
	for (page=0; page < num_pages; page++)
	{
		pdf_obj *page_obj = pdf_lookup_page_obj(ctx, doc, page);
		int xf = x_factor, yf = y_factor;
		float w, h;
		int x, y;

		rotate = pdf_to_int(ctx, pdf_dict_get_inheritable(ctx, page_obj, PDF_NAME(Rotate)));
		mediabox = pdf_to_rect(ctx, pdf_dict_get_inheritable(ctx, page_obj, PDF_NAME(MediaBox)));
		cropbox = pdf_to_rect(ctx, pdf_dict_get_inheritable(ctx, page_obj, PDF_NAME(CropBox)));
		if (fz_is_empty_rect(mediabox))
			mediabox = fz_make_rect(0, 0, 612, 792);
		if (!fz_is_empty_rect(cropbox))
			mediabox = fz_intersect_rect(mediabox, cropbox);

		w = mediabox.x1 - mediabox.x0;
		h = mediabox.y1 - mediabox.y0;

		if (rotate == 90 || rotate == 270)
		{
			xf = y_factor;
			yf = x_factor;
		}
		else
		{
			xf = x_factor;
			yf = y_factor;
		}

		if (xf == 0 && yf == 0)
		{
			/* Nothing specified, so split along the long edge */
			if (w > h)
				xf = 2, yf = 1;
			else
				xf = 1, yf = 2;
		}
		else if (xf == 0)
			xf = 1;
		else if (yf == 0)
			yf = 1;

		for (y = yf-1; y >= 0; y--)
		{
			for (x = 0; x < xf; x++)
			{
				pdf_obj *newpageobj, *newpageref, *newmediabox;
				fz_rect mb;

				newpageobj = pdf_copy_dict(ctx, pdf_lookup_page_obj(ctx, doc, page));
				pdf_flatten_inheritable_page_items(ctx, newpageobj);
				newpageref = pdf_add_object(ctx, doc, newpageobj);

				newmediabox = pdf_new_array(ctx, doc, 4);

				mb.x0 = mediabox.x0 + (w/xf)*x;
				if (x == xf-1)
					mb.x1 = mediabox.x1;
				else
					mb.x1 = mediabox.x0 + (w/xf)*(x+1);
				mb.y0 = mediabox.y0 + (h/yf)*y;
				if (y == yf-1)
					mb.y1 = mediabox.y1;
				else
					mb.y1 = mediabox.y0 + (h/yf)*(y+1);

				pdf_array_push_real(ctx, newmediabox, mb.x0);
				pdf_array_push_real(ctx, newmediabox, mb.y0);
				pdf_array_push_real(ctx, newmediabox, mb.x1);
				pdf_array_push_real(ctx, newmediabox, mb.y1);

				pdf_dict_put(ctx, newpageobj, PDF_NAME(Parent), pages);
				pdf_dict_put_drop(ctx, newpageobj, PDF_NAME(MediaBox), newmediabox);

				intersect_box(ctx, doc, newpageobj, PDF_NAME(CropBox), mb);
				intersect_box(ctx, doc, newpageobj, PDF_NAME(BleedBox), mb);
				intersect_box(ctx, doc, newpageobj, PDF_NAME(TrimBox), mb);
				intersect_box(ctx, doc, newpageobj, PDF_NAME(ArtBox), mb);

				/* Store page object in new kids array */
				pdf_drop_obj(ctx, newpageobj);
				pdf_array_push_drop(ctx, kids, newpageref);

				kidcount++;
			}
		}
	}

	/* Update page count and kids array */
	pdf_dict_put_int(ctx, pages, PDF_NAME(Count), kidcount);
	pdf_dict_put_drop(ctx, pages, PDF_NAME(Kids), kids);
}