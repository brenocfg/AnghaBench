#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ linear_page_count; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
pdf_count_pages(fz_context *ctx, pdf_document *doc)
{
	/* FIXME: We should reset linear_page_count to 0 when editing starts
	 * (or when linear loading ends) */
	if (doc->linear_page_count != 0)
		return doc->linear_page_count;
	return pdf_to_int(ctx, pdf_dict_getp(ctx, pdf_trailer(ctx, doc), "Root/Pages/Count"));
}