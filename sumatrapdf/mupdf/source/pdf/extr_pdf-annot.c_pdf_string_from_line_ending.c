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
#define  PDF_ANNOT_LE_BUTT 137 
#define  PDF_ANNOT_LE_CIRCLE 136 
#define  PDF_ANNOT_LE_CLOSED_ARROW 135 
#define  PDF_ANNOT_LE_DIAMOND 134 
#define  PDF_ANNOT_LE_NONE 133 
#define  PDF_ANNOT_LE_OPEN_ARROW 132 
#define  PDF_ANNOT_LE_R_CLOSED_ARROW 131 
#define  PDF_ANNOT_LE_R_OPEN_ARROW 130 
#define  PDF_ANNOT_LE_SLASH 129 
#define  PDF_ANNOT_LE_SQUARE 128 

const char *pdf_string_from_line_ending(fz_context *ctx, enum pdf_line_ending end)
{
	switch (end)
	{
	default:
	case PDF_ANNOT_LE_NONE: return "None";
	case PDF_ANNOT_LE_SQUARE: return "Square";
	case PDF_ANNOT_LE_CIRCLE: return "Circle";
	case PDF_ANNOT_LE_DIAMOND: return "Diamond";
	case PDF_ANNOT_LE_OPEN_ARROW: return "OpenArrow";
	case PDF_ANNOT_LE_CLOSED_ARROW: return "ClosedArrow";
	case PDF_ANNOT_LE_BUTT: return "Butt";
	case PDF_ANNOT_LE_R_OPEN_ARROW: return "ROpenArrow";
	case PDF_ANNOT_LE_R_CLOSED_ARROW: return "RClosedArrow";
	case PDF_ANNOT_LE_SLASH: return "Slash";
	}
}