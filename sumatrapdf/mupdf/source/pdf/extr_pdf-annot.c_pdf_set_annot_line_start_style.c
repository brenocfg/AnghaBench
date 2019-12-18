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
typedef  int /*<<< orphan*/  pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  enum pdf_line_ending { ____Placeholder_pdf_line_ending } pdf_line_ending ;

/* Variables and functions */
 int pdf_annot_line_end_style (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_set_annot_line_ending_styles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void
pdf_set_annot_line_start_style(fz_context *ctx, pdf_annot *annot, enum pdf_line_ending s)
{
	enum pdf_line_ending e = pdf_annot_line_end_style(ctx, annot);
	pdf_set_annot_line_ending_styles(ctx, annot, s, e);
}