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
#define  PDF_ANNOT_CIRCLE 134 
#define  PDF_ANNOT_FREE_TEXT 133 
#define  PDF_ANNOT_INK 132 
#define  PDF_ANNOT_LINE 131 
#define  PDF_ANNOT_POLYGON 130 
#define  PDF_ANNOT_POLY_LINE 129 
#define  PDF_ANNOT_SQUARE 128 

__attribute__((used)) static int should_edit_border(enum pdf_annot_type subtype)
{
	switch (subtype) {
	default:
		return 0;
	case PDF_ANNOT_FREE_TEXT:
		return 1;
	case PDF_ANNOT_INK:
	case PDF_ANNOT_LINE:
	case PDF_ANNOT_SQUARE:
	case PDF_ANNOT_CIRCLE:
	case PDF_ANNOT_POLYGON:
	case PDF_ANNOT_POLY_LINE:
		return 1;
	}
}