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
 int /*<<< orphan*/  Exclude ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_field_hierarchy_to_array(fz_context *ctx, pdf_obj *array, pdf_obj *field)
{
	pdf_obj *kids = pdf_dict_get(ctx, field, PDF_NAME(Kids));
	pdf_obj *exclude = pdf_dict_get(ctx, field, PDF_NAME(Exclude));

	if (exclude)
		return;

	pdf_array_push(ctx, array, field);

	if (kids)
	{
		int i, n = pdf_array_len(ctx, kids);

		for (i = 0; i < n; i++)
			add_field_hierarchy_to_array(ctx, array, pdf_array_get(ctx, kids, i));
	}
}