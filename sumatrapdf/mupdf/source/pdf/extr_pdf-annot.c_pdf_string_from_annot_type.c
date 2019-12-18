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
typedef  enum pdf_annot_type { ____Placeholder_pdf_annot_type } pdf_annot_type ;

/* Variables and functions */
#define  PDF_ANNOT_3D 153 
#define  PDF_ANNOT_CARET 152 
#define  PDF_ANNOT_CIRCLE 151 
#define  PDF_ANNOT_FILE_ATTACHMENT 150 
#define  PDF_ANNOT_FREE_TEXT 149 
#define  PDF_ANNOT_HIGHLIGHT 148 
#define  PDF_ANNOT_INK 147 
#define  PDF_ANNOT_LINE 146 
#define  PDF_ANNOT_LINK 145 
#define  PDF_ANNOT_MOVIE 144 
#define  PDF_ANNOT_POLYGON 143 
#define  PDF_ANNOT_POLY_LINE 142 
#define  PDF_ANNOT_POPUP 141 
#define  PDF_ANNOT_PRINTER_MARK 140 
#define  PDF_ANNOT_REDACT 139 
#define  PDF_ANNOT_SCREEN 138 
#define  PDF_ANNOT_SOUND 137 
#define  PDF_ANNOT_SQUARE 136 
#define  PDF_ANNOT_SQUIGGLY 135 
#define  PDF_ANNOT_STAMP 134 
#define  PDF_ANNOT_STRIKE_OUT 133 
#define  PDF_ANNOT_TEXT 132 
#define  PDF_ANNOT_TRAP_NET 131 
#define  PDF_ANNOT_UNDERLINE 130 
#define  PDF_ANNOT_WATERMARK 129 
#define  PDF_ANNOT_WIDGET 128 

const char *
pdf_string_from_annot_type(fz_context *ctx, enum pdf_annot_type type)
{
	switch (type)
	{
	case PDF_ANNOT_TEXT: return "Text";
	case PDF_ANNOT_LINK: return "Link";
	case PDF_ANNOT_FREE_TEXT: return "FreeText";
	case PDF_ANNOT_LINE: return "Line";
	case PDF_ANNOT_SQUARE: return "Square";
	case PDF_ANNOT_CIRCLE: return "Circle";
	case PDF_ANNOT_POLYGON: return "Polygon";
	case PDF_ANNOT_POLY_LINE: return "PolyLine";
	case PDF_ANNOT_HIGHLIGHT: return "Highlight";
	case PDF_ANNOT_UNDERLINE: return "Underline";
	case PDF_ANNOT_SQUIGGLY: return "Squiggly";
	case PDF_ANNOT_STRIKE_OUT: return "StrikeOut";
	case PDF_ANNOT_REDACT: return "Redact";
	case PDF_ANNOT_STAMP: return "Stamp";
	case PDF_ANNOT_CARET: return "Caret";
	case PDF_ANNOT_INK: return "Ink";
	case PDF_ANNOT_POPUP: return "Popup";
	case PDF_ANNOT_FILE_ATTACHMENT: return "FileAttachment";
	case PDF_ANNOT_SOUND: return "Sound";
	case PDF_ANNOT_MOVIE: return "Movie";
	case PDF_ANNOT_WIDGET: return "Widget";
	case PDF_ANNOT_SCREEN: return "Screen";
	case PDF_ANNOT_PRINTER_MARK: return "PrinterMark";
	case PDF_ANNOT_TRAP_NET: return "TrapNet";
	case PDF_ANNOT_WATERMARK: return "Watermark";
	case PDF_ANNOT_3D: return "3D";
	default: return "UNKNOWN";
	}
}