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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Count ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int INT_MAX ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pages ; 
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_array_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_lookup_page_loc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_insert_page(fz_context *ctx, pdf_document *doc, int at, pdf_obj *page_ref)
{
	int count = pdf_count_pages(ctx, doc);
	pdf_obj *parent, *kids;
	int i;

	if (at < 0)
		at = count;
	if (at == INT_MAX)
		at = count;
	if (at > count)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot insert page beyond end of page tree");

	if (count == 0)
	{
		pdf_obj *root = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Root));
		parent = pdf_dict_get(ctx, root, PDF_NAME(Pages));
		if (!parent)
			fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find page tree");
		kids = pdf_dict_get(ctx, parent, PDF_NAME(Kids));
		if (!kids)
			fz_throw(ctx, FZ_ERROR_GENERIC, "malformed page tree");
		pdf_array_insert(ctx, kids, page_ref, 0);
	}
	else if (at == count)
	{
		/* append after last page */
		pdf_lookup_page_loc(ctx, doc, count - 1, &parent, &i);
		kids = pdf_dict_get(ctx, parent, PDF_NAME(Kids));
		pdf_array_insert(ctx, kids, page_ref, i + 1);
	}
	else
	{
		/* insert before found page */
		pdf_lookup_page_loc(ctx, doc, at, &parent, &i);
		kids = pdf_dict_get(ctx, parent, PDF_NAME(Kids));
		pdf_array_insert(ctx, kids, page_ref, i);
	}

	pdf_dict_put(ctx, page_ref, PDF_NAME(Parent), parent);

	/* Adjust page counts */
	while (parent)
	{
		count = pdf_dict_get_int(ctx, parent, PDF_NAME(Count));
		pdf_dict_put_int(ctx, parent, PDF_NAME(Count), count + 1);
		parent = pdf_dict_get(ctx, parent, PDF_NAME(Parent));
	}
}