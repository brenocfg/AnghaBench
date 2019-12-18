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
typedef  enum pdf_line_ending { ____Placeholder_pdf_line_ending } pdf_line_ending ;

/* Variables and functions */
 int /*<<< orphan*/  Butt ; 
 int /*<<< orphan*/  Circle ; 
 int /*<<< orphan*/  ClosedArrow ; 
 int /*<<< orphan*/  Diamond ; 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  OpenArrow ; 
 int PDF_ANNOT_LE_BUTT ; 
 int PDF_ANNOT_LE_CIRCLE ; 
 int PDF_ANNOT_LE_CLOSED_ARROW ; 
 int PDF_ANNOT_LE_DIAMOND ; 
 int PDF_ANNOT_LE_NONE ; 
 int PDF_ANNOT_LE_OPEN_ARROW ; 
 int PDF_ANNOT_LE_R_CLOSED_ARROW ; 
 int PDF_ANNOT_LE_R_OPEN_ARROW ; 
 int PDF_ANNOT_LE_SLASH ; 
 int PDF_ANNOT_LE_SQUARE ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RClosedArrow ; 
 int /*<<< orphan*/  ROpenArrow ; 
 int /*<<< orphan*/  Slash ; 
 int /*<<< orphan*/  Square ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum pdf_line_ending pdf_line_ending_from_name(fz_context *ctx, pdf_obj *end)
{
	if (pdf_name_eq(ctx, end, PDF_NAME(None))) return PDF_ANNOT_LE_NONE;
	else if (pdf_name_eq(ctx, end, PDF_NAME(Square))) return PDF_ANNOT_LE_SQUARE;
	else if (pdf_name_eq(ctx, end, PDF_NAME(Circle))) return PDF_ANNOT_LE_CIRCLE;
	else if (pdf_name_eq(ctx, end, PDF_NAME(Diamond))) return PDF_ANNOT_LE_DIAMOND;
	else if (pdf_name_eq(ctx, end, PDF_NAME(OpenArrow))) return PDF_ANNOT_LE_OPEN_ARROW;
	else if (pdf_name_eq(ctx, end, PDF_NAME(ClosedArrow))) return PDF_ANNOT_LE_CLOSED_ARROW;
	else if (pdf_name_eq(ctx, end, PDF_NAME(Butt))) return PDF_ANNOT_LE_BUTT;
	else if (pdf_name_eq(ctx, end, PDF_NAME(ROpenArrow))) return PDF_ANNOT_LE_R_OPEN_ARROW;
	else if (pdf_name_eq(ctx, end, PDF_NAME(RClosedArrow))) return PDF_ANNOT_LE_R_CLOSED_ARROW;
	else if (pdf_name_eq(ctx, end, PDF_NAME(Slash))) return PDF_ANNOT_LE_SLASH;
	else return PDF_ANNOT_LE_NONE;
}