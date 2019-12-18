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
typedef  int /*<<< orphan*/  fz_context ;
typedef  enum pdf_line_ending { ____Placeholder_pdf_line_ending } pdf_line_ending ;

/* Variables and functions */
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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

enum pdf_line_ending pdf_line_ending_from_string(fz_context *ctx, const char *end)
{
	if (!strcmp(end, "None")) return PDF_ANNOT_LE_NONE;
	else if (!strcmp(end, "Square")) return PDF_ANNOT_LE_SQUARE;
	else if (!strcmp(end, "Circle")) return PDF_ANNOT_LE_CIRCLE;
	else if (!strcmp(end, "Diamond")) return PDF_ANNOT_LE_DIAMOND;
	else if (!strcmp(end, "OpenArrow")) return PDF_ANNOT_LE_OPEN_ARROW;
	else if (!strcmp(end, "ClosedArrow")) return PDF_ANNOT_LE_CLOSED_ARROW;
	else if (!strcmp(end, "Butt")) return PDF_ANNOT_LE_BUTT;
	else if (!strcmp(end, "ROpenArrow")) return PDF_ANNOT_LE_R_OPEN_ARROW;
	else if (!strcmp(end, "RClosedArrow")) return PDF_ANNOT_LE_R_CLOSED_ARROW;
	else if (!strcmp(end, "Slash")) return PDF_ANNOT_LE_SLASH;
	else return PDF_ANNOT_LE_NONE;
}