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
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/  pdf_array_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_lookup_page_loc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 

void
pdf_delete_page(fz_context *ctx, pdf_document *doc, int at)
{
	pdf_obj *parent, *kids;
	int i;

	pdf_lookup_page_loc(ctx, doc, at, &parent, &i);
	kids = pdf_dict_get(ctx, parent, PDF_NAME(Kids));
	pdf_array_delete(ctx, kids, i);

	while (parent)
	{
		int count = pdf_dict_get_int(ctx, parent, PDF_NAME(Count));
		pdf_dict_put_int(ctx, parent, PDF_NAME(Count), count - 1);
		parent = pdf_dict_get(ctx, parent, PDF_NAME(Parent));
	}
}