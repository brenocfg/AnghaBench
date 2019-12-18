#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_text_filter_fn ;
typedef  int /*<<< orphan*/  pdf_page_contents_process_fn ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  pdf_after_text_object_fn ;
typedef  int /*<<< orphan*/  fz_cookie ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AP ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_clean_stream_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pdf_filter_annot_contents(fz_context *ctx, pdf_document *doc, pdf_annot *annot, fz_cookie *cookie,
	pdf_page_contents_process_fn *proc, pdf_text_filter_fn *text_filter, pdf_after_text_object_fn *after_text, void *arg, int sanitize, int ascii)
{
	pdf_obj *ap;
	int i, n;

	ap = pdf_dict_get(ctx, annot->obj, PDF_NAME(AP));
	if (ap == NULL)
		return;

	n = pdf_dict_len(ctx, ap);
	for (i = 0; i < n; i++)
	{
		pdf_obj *v = pdf_dict_get_val(ctx, ap, i);

		if (v == NULL)
			continue;

		pdf_clean_stream_object(ctx, doc, v, NULL, cookie, 1, text_filter, after_text, arg, sanitize, ascii);
	}
}