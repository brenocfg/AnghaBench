#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int no_black_boxes; } ;
typedef  TYPE_1__ pdf_redact_options ;
typedef  int /*<<< orphan*/  pdf_page ;
struct TYPE_12__ {int redacted; } ;
typedef  TYPE_2__ pdf_document ;
struct TYPE_13__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_3__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Redact ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  pdf_delete_annot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pdf_filter_page_contents (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 TYPE_3__* pdf_first_annot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* pdf_next_annot (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * pdf_redact_end_page ; 
 int /*<<< orphan*/  pdf_redact_text_filter ; 

int
pdf_redact_page(fz_context *ctx, pdf_document *doc, pdf_page *page, pdf_redact_options *opts)
{
	pdf_annot *annot;
	int has_redactions = 0;
	int no_black_boxes = 0;

	if (opts)
	{
		no_black_boxes = opts->no_black_boxes;
	}

	for (annot = pdf_first_annot(ctx, page); annot; annot = pdf_next_annot(ctx, annot))
		if (pdf_dict_get(ctx, annot->obj, PDF_NAME(Subtype)) == PDF_NAME(Redact))
			has_redactions = 1;

	if (has_redactions)
	{
		pdf_filter_page_contents(ctx, doc, page, NULL,
			no_black_boxes ? NULL : pdf_redact_end_page,
			pdf_redact_text_filter,
			NULL,
			page,
			1, 1);
	}

	annot = pdf_first_annot(ctx, page);
	while (annot)
	{
		if (pdf_dict_get(ctx, annot->obj, PDF_NAME(Subtype)) == PDF_NAME(Redact))
		{
			pdf_delete_annot(ctx, page, annot);
			annot = pdf_first_annot(ctx, page);
		}
		else
		{
			annot = pdf_next_annot(ctx, annot);
		}
	}

	doc->redacted = has_redactions;

	return has_redactions;
}