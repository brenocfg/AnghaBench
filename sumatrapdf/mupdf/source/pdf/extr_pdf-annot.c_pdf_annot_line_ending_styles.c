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
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  enum pdf_line_ending { ____Placeholder_pdf_line_ending } pdf_line_ending ;

/* Variables and functions */
 int /*<<< orphan*/  LE ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_ending_subtypes ; 
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_line_ending_from_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pdf_annot_line_ending_styles(fz_context *ctx, pdf_annot *annot,
		enum pdf_line_ending *start_style,
		enum pdf_line_ending *end_style)
{
	pdf_obj *style;
	check_allowed_subtypes(ctx, annot, PDF_NAME(LE), line_ending_subtypes);
	style = pdf_dict_get(ctx, annot->obj, PDF_NAME(LE));
	*start_style = pdf_line_ending_from_name(ctx, pdf_array_get(ctx, style, 0));
	*end_style = pdf_line_ending_from_name(ctx, pdf_array_get(ctx, style, 1));
}