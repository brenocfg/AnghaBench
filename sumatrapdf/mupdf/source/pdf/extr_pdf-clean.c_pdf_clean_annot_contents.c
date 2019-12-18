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
typedef  int /*<<< orphan*/  pdf_page_contents_process_fn ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  pdf_annot ;
typedef  int /*<<< orphan*/  fz_cookie ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_filter_annot_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int) ; 

void pdf_clean_annot_contents(fz_context *ctx, pdf_document *doc, pdf_annot *annot, fz_cookie *cookie, pdf_page_contents_process_fn *proc_fn, void *proc_arg, int sanitize, int ascii)
{
	pdf_filter_annot_contents(ctx, doc, annot, cookie, proc_fn, NULL, NULL, proc_arg, sanitize, ascii);
}