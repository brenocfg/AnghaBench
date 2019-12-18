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
 int /*<<< orphan*/  CropBox ; 
 int /*<<< orphan*/  MediaBox ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Resources ; 
 int /*<<< orphan*/  Rotate ; 
 int /*<<< orphan*/  pdf_flatten_inheritable_page_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pdf_flatten_inheritable_page_items(fz_context *ctx, pdf_obj *page)
{
	pdf_flatten_inheritable_page_item(ctx, page, PDF_NAME(MediaBox));
	pdf_flatten_inheritable_page_item(ctx, page, PDF_NAME(CropBox));
	pdf_flatten_inheritable_page_item(ctx, page, PDF_NAME(Rotate));
	pdf_flatten_inheritable_page_item(ctx, page, PDF_NAME(Resources));
}