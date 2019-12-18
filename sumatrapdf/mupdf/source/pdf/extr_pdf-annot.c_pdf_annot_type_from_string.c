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

/* Variables and functions */
 int PDF_ANNOT_3D ; 
 int PDF_ANNOT_CARET ; 
 int PDF_ANNOT_CIRCLE ; 
 int PDF_ANNOT_FILE_ATTACHMENT ; 
 int PDF_ANNOT_FREE_TEXT ; 
 int PDF_ANNOT_HIGHLIGHT ; 
 int PDF_ANNOT_INK ; 
 int PDF_ANNOT_LINE ; 
 int PDF_ANNOT_LINK ; 
 int PDF_ANNOT_MOVIE ; 
 int PDF_ANNOT_POLYGON ; 
 int PDF_ANNOT_POLY_LINE ; 
 int PDF_ANNOT_POPUP ; 
 int PDF_ANNOT_PRINTER_MARK ; 
 int PDF_ANNOT_REDACT ; 
 int PDF_ANNOT_SCREEN ; 
 int PDF_ANNOT_SOUND ; 
 int PDF_ANNOT_SQUARE ; 
 int PDF_ANNOT_SQUIGGLY ; 
 int PDF_ANNOT_STAMP ; 
 int PDF_ANNOT_STRIKE_OUT ; 
 int PDF_ANNOT_TEXT ; 
 int PDF_ANNOT_TRAP_NET ; 
 int PDF_ANNOT_UNDERLINE ; 
 int PDF_ANNOT_UNKNOWN ; 
 int PDF_ANNOT_WATERMARK ; 
 int PDF_ANNOT_WIDGET ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int
pdf_annot_type_from_string(fz_context *ctx, const char *subtype)
{
	if (!strcmp("Text", subtype)) return PDF_ANNOT_TEXT;
	if (!strcmp("Link", subtype)) return PDF_ANNOT_LINK;
	if (!strcmp("FreeText", subtype)) return PDF_ANNOT_FREE_TEXT;
	if (!strcmp("Line", subtype)) return PDF_ANNOT_LINE;
	if (!strcmp("Square", subtype)) return PDF_ANNOT_SQUARE;
	if (!strcmp("Circle", subtype)) return PDF_ANNOT_CIRCLE;
	if (!strcmp("Polygon", subtype)) return PDF_ANNOT_POLYGON;
	if (!strcmp("PolyLine", subtype)) return PDF_ANNOT_POLY_LINE;
	if (!strcmp("Highlight", subtype)) return PDF_ANNOT_HIGHLIGHT;
	if (!strcmp("Underline", subtype)) return PDF_ANNOT_UNDERLINE;
	if (!strcmp("Squiggly", subtype)) return PDF_ANNOT_SQUIGGLY;
	if (!strcmp("StrikeOut", subtype)) return PDF_ANNOT_STRIKE_OUT;
	if (!strcmp("Redact", subtype)) return PDF_ANNOT_REDACT;
	if (!strcmp("Stamp", subtype)) return PDF_ANNOT_STAMP;
	if (!strcmp("Caret", subtype)) return PDF_ANNOT_CARET;
	if (!strcmp("Ink", subtype)) return PDF_ANNOT_INK;
	if (!strcmp("Popup", subtype)) return PDF_ANNOT_POPUP;
	if (!strcmp("FileAttachment", subtype)) return PDF_ANNOT_FILE_ATTACHMENT;
	if (!strcmp("Sound", subtype)) return PDF_ANNOT_SOUND;
	if (!strcmp("Movie", subtype)) return PDF_ANNOT_MOVIE;
	if (!strcmp("Widget", subtype)) return PDF_ANNOT_WIDGET;
	if (!strcmp("Screen", subtype)) return PDF_ANNOT_SCREEN;
	if (!strcmp("PrinterMark", subtype)) return PDF_ANNOT_PRINTER_MARK;
	if (!strcmp("TrapNet", subtype)) return PDF_ANNOT_TRAP_NET;
	if (!strcmp("Watermark", subtype)) return PDF_ANNOT_WATERMARK;
	if (!strcmp("3D", subtype)) return PDF_ANNOT_3D;
	return PDF_ANNOT_UNKNOWN;
}