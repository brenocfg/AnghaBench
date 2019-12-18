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
 int /*<<< orphan*/  Opt ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* pdf_array_get_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pdf_choice_widget_options(fz_context *ctx, pdf_widget *tw, int exportval, const char *opts[])
{
	pdf_annot *annot = (pdf_annot *)tw;
	pdf_obj *optarr;
	int i, n, m;

	optarr = pdf_dict_get_inheritable(ctx, annot->obj, PDF_NAME(Opt));
	n = pdf_array_len(ctx, optarr);

	if (opts)
	{
		for (i = 0; i < n; i++)
		{
			m = pdf_array_len(ctx, pdf_array_get(ctx, optarr, i));
			/* If it is a two element array, the second item is the one that we want if we want the listing value. */
			if (m == 2)
				if (exportval)
					opts[i] = pdf_array_get_text_string(ctx, pdf_array_get(ctx, optarr, i), 0);
				else
					opts[i] = pdf_array_get_text_string(ctx, pdf_array_get(ctx, optarr, i), 1);
			else
				opts[i] = pdf_array_get_text_string(ctx, optarr, i);
		}
	}
	return n;
}