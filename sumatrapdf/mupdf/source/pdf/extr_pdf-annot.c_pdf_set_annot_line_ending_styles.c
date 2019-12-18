#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_7__ {int /*<<< orphan*/  obj; TYPE_1__* page; } ;
typedef  TYPE_2__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  enum pdf_line_ending { ____Placeholder_pdf_line_ending } pdf_line_ending ;
struct TYPE_6__ {int /*<<< orphan*/ * doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_ending_subtypes ; 
 int /*<<< orphan*/  pdf_array_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dirty_annot (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_name_from_line_ending (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
pdf_set_annot_line_ending_styles(fz_context *ctx, pdf_annot *annot,
		enum pdf_line_ending start_style,
		enum pdf_line_ending end_style)
{
	pdf_document *doc = annot->page->doc;
	pdf_obj *style;
	check_allowed_subtypes(ctx, annot, PDF_NAME(LE), line_ending_subtypes);
	style = pdf_new_array(ctx, doc, 2);
	pdf_dict_put_drop(ctx, annot->obj, PDF_NAME(LE), style);
	pdf_array_put_drop(ctx, style, 0, pdf_name_from_line_ending(ctx, start_style));
	pdf_array_put_drop(ctx, style, 1, pdf_name_from_line_ending(ctx, end_style));
	pdf_dirty_annot(ctx, annot);
}