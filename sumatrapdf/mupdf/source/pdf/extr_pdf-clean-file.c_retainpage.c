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
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/  pdf_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_flatten_inheritable_page_items (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_lookup_page_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void retainpage(fz_context *ctx, pdf_document *doc, pdf_obj *parent, pdf_obj *kids, int page)
{
	pdf_obj *pageref = pdf_lookup_page_obj(ctx, doc, page-1);

	pdf_flatten_inheritable_page_items(ctx, pageref);

	pdf_dict_put(ctx, pageref, PDF_NAME(Parent), parent);

	/* Store page object in new kids array */
	pdf_array_push(ctx, kids, pageref);
}