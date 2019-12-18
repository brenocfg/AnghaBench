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
typedef  enum pdf_annot_type { ____Placeholder_pdf_annot_type } pdf_annot_type ;

/* Variables and functions */
#define  PDF_ANNOT_CARET 143 
#define  PDF_ANNOT_CIRCLE 142 
#define  PDF_ANNOT_FILE_ATTACHMENT 141 
#define  PDF_ANNOT_FREE_TEXT 140 
#define  PDF_ANNOT_HIGHLIGHT 139 
#define  PDF_ANNOT_INK 138 
#define  PDF_ANNOT_LINE 137 
#define  PDF_ANNOT_POLYGON 136 
#define  PDF_ANNOT_POLY_LINE 135 
#define  PDF_ANNOT_SOUND 134 
#define  PDF_ANNOT_SQUARE 133 
#define  PDF_ANNOT_SQUIGGLY 132 
#define  PDF_ANNOT_STAMP 131 
#define  PDF_ANNOT_STRIKE_OUT 130 
#define  PDF_ANNOT_TEXT 129 
#define  PDF_ANNOT_UNDERLINE 128 

__attribute__((used)) static int should_edit_color(enum pdf_annot_type subtype)
{
	switch (subtype) {
	default:
		return 0;
	case PDF_ANNOT_STAMP:
	case PDF_ANNOT_TEXT:
	case PDF_ANNOT_FILE_ATTACHMENT:
	case PDF_ANNOT_SOUND:
	case PDF_ANNOT_CARET:
		return 1;
	case PDF_ANNOT_FREE_TEXT:
		return 1;
	case PDF_ANNOT_INK:
	case PDF_ANNOT_LINE:
	case PDF_ANNOT_SQUARE:
	case PDF_ANNOT_CIRCLE:
	case PDF_ANNOT_POLYGON:
	case PDF_ANNOT_POLY_LINE:
		return 1;
	case PDF_ANNOT_HIGHLIGHT:
	case PDF_ANNOT_UNDERLINE:
	case PDF_ANNOT_STRIKE_OUT:
	case PDF_ANNOT_SQUIGGLY:
		return 1;
	}
}