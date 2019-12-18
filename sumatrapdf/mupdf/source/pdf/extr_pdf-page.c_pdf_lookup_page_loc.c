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
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pages ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_lookup_page_loc_imp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_lookup_page_loc(fz_context *ctx, pdf_document *doc, int needle, pdf_obj **parentp, int *indexp)
{
	pdf_obj *root = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Root));
	pdf_obj *node = pdf_dict_get(ctx, root, PDF_NAME(Pages));
	int skip = needle;
	pdf_obj *hit;

	if (!node)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find page tree");

	hit = pdf_lookup_page_loc_imp(ctx, doc, node, &skip, parentp, indexp);
	if (!hit)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find page %d in page tree", needle+1);
	return hit;
}