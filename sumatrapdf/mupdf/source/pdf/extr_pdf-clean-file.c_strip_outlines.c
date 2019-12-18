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
 int /*<<< orphan*/  First ; 
 int /*<<< orphan*/  Last ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strip_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int strip_outlines(fz_context *ctx, pdf_document *doc, pdf_obj *outlines, int page_count, int *page_object_nums, pdf_obj *names_list)
{
	int nc;
	pdf_obj *first;
	pdf_obj *last;

	if (outlines == NULL)
		return 0;

	first = pdf_dict_get(ctx, outlines, PDF_NAME(First));
	if (first == NULL)
		nc = 0;
	else
		nc = strip_outline(ctx, doc, first, page_count, page_object_nums, names_list, &first, &last);

	if (nc == 0)
	{
		pdf_dict_del(ctx, outlines, PDF_NAME(First));
		pdf_dict_del(ctx, outlines, PDF_NAME(Last));
		pdf_dict_del(ctx, outlines, PDF_NAME(Count));
	}
	else
	{
		int old_count = pdf_dict_get_int(ctx, outlines, PDF_NAME(Count));
		pdf_dict_put(ctx, outlines, PDF_NAME(First), first);
		pdf_dict_put(ctx, outlines, PDF_NAME(Last), last);
		pdf_dict_put_int(ctx, outlines, PDF_NAME(Count), old_count > 0 ? nc : -nc);
	}

	return nc;
}