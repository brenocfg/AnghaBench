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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_delete_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
pdf_delete_page_range(fz_context *ctx, pdf_document *doc, int start, int end)
{
	int count = pdf_count_pages(ctx, doc);

	if (end < 0 || end > count)
		end = count+1;
	if (start < 0)
		start = 0;
	while (start < end)
	{
		pdf_delete_page(ctx, doc, start);
		end--;
	}
}