#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* annots; } ;
typedef  TYPE_1__ pdf_page ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_2__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
struct TYPE_11__ {int progress_max; int /*<<< orphan*/  progress; scalar_t__ abort; } ;
typedef  TYPE_3__ fz_cookie ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_run_annot_with_usage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_3__*) ; 

__attribute__((used)) static void
pdf_run_page_annots_with_usage(fz_context *ctx, pdf_document *doc, pdf_page *page, fz_device *dev, fz_matrix ctm, const char *usage, fz_cookie *cookie)
{
	pdf_annot *annot;

	if (cookie && cookie->progress_max != -1)
	{
		int count = 1;
		for (annot = page->annots; annot; annot = annot->next)
			count++;
		cookie->progress_max += count;
	}

	for (annot = page->annots; annot; annot = annot->next)
	{
		/* Check the cookie for aborting */
		if (cookie)
		{
			if (cookie->abort)
				break;
			cookie->progress++;
		}

		pdf_run_annot_with_usage(ctx, doc, page, annot, dev, ctm, usage, cookie);
	}
}