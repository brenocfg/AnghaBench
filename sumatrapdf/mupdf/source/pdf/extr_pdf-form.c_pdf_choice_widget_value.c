#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_widget ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_to_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pdf_choice_widget_value(fz_context *ctx, pdf_widget *tw, const char *opts[])
{
	pdf_annot *annot = (pdf_annot *)tw;
	pdf_obj *optarr;
	int i, n;

	if (!annot)
		return 0;

	optarr = pdf_dict_get(ctx, annot->obj, PDF_NAME(V));

	if (pdf_is_string(ctx, optarr))
	{
		if (opts)
			opts[0] = pdf_to_text_string(ctx, optarr);
		return 1;
	}
	else
	{
		n = pdf_array_len(ctx, optarr);
		if (opts)
		{
			for (i = 0; i < n; i++)
			{
				pdf_obj *elem = pdf_array_get(ctx, optarr, i);
				if (pdf_is_array(ctx, elem))
					elem = pdf_array_get(ctx, elem, 1);
				opts[i] = pdf_to_text_string(ctx, elem);
			}
		}
		return n;
	}
}