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
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  Dest ; 
 int /*<<< orphan*/  GoTo ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  dest_is_valid_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int string_in_names_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dest_is_valid(fz_context *ctx, pdf_obj *o, int page_count, int *page_object_nums, pdf_obj *names_list)
{
	pdf_obj *p;

	p = pdf_dict_get(ctx, o, PDF_NAME(A));
	if (pdf_name_eq(ctx, pdf_dict_get(ctx, p, PDF_NAME(S)), PDF_NAME(GoTo)) &&
		!string_in_names_list(ctx, pdf_dict_get(ctx, p, PDF_NAME(D)), names_list))
		return 0;

	p = pdf_dict_get(ctx, o, PDF_NAME(Dest));
	if (p == NULL)
	{}
	else if (pdf_is_string(ctx, p))
		return string_in_names_list(ctx, p, names_list);
	else if (!dest_is_valid_page(ctx, pdf_array_get(ctx, p, 0), page_object_nums, page_count))
		return 0;

	return 1;
}