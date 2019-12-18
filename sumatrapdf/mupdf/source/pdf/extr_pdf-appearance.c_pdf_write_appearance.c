#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_19__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
#define  PDF_ANNOT_CARET 145 
#define  PDF_ANNOT_CIRCLE 144 
#define  PDF_ANNOT_FILE_ATTACHMENT 143 
#define  PDF_ANNOT_FREE_TEXT 142 
#define  PDF_ANNOT_HIGHLIGHT 141 
#define  PDF_ANNOT_INK 140 
#define  PDF_ANNOT_LINE 139 
#define  PDF_ANNOT_POLYGON 138 
#define  PDF_ANNOT_POLY_LINE 137 
#define  PDF_ANNOT_REDACT 136 
#define  PDF_ANNOT_SOUND 135 
#define  PDF_ANNOT_SQUARE 134 
#define  PDF_ANNOT_SQUIGGLY 133 
#define  PDF_ANNOT_STAMP 132 
#define  PDF_ANNOT_STRIKE_OUT 131 
#define  PDF_ANNOT_TEXT 130 
#define  PDF_ANNOT_UNDERLINE 129 
#define  PDF_ANNOT_WIDGET 128 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  fz_identity ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pdf_annot_type (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_dict_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_write_caret_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_circle_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_free_text_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pdf_write_highlight_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pdf_write_icon_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_ink_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_line_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_polygon_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_write_redact_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_square_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_squiggly_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_stamp_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pdf_write_strike_out_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_underline_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_widget_appearance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
pdf_write_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf,
	fz_rect *rect, fz_rect *bbox, fz_matrix *matrix, pdf_obj **res)
{
	switch (pdf_annot_type(ctx, annot))
	{
	default:
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot create appearance stream for %s annotations",
			pdf_dict_get_name(ctx, annot->obj, PDF_NAME(Subtype)));
	case PDF_ANNOT_WIDGET:
		pdf_write_widget_appearance(ctx, annot, buf, rect, bbox, matrix, res);
		break;
	case PDF_ANNOT_INK:
		pdf_write_ink_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_POLYGON:
		pdf_write_polygon_appearance(ctx, annot, buf, rect, 1);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_POLY_LINE:
		pdf_write_polygon_appearance(ctx, annot, buf, rect, 0);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_LINE:
		pdf_write_line_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_SQUARE:
		pdf_write_square_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_CIRCLE:
		pdf_write_circle_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_CARET:
		pdf_write_caret_appearance(ctx, annot, buf, rect, bbox);
		*matrix = fz_identity;
		break;
	case PDF_ANNOT_TEXT:
	case PDF_ANNOT_FILE_ATTACHMENT:
	case PDF_ANNOT_SOUND:
		pdf_write_icon_appearance(ctx, annot, buf, rect, bbox);
		*matrix = fz_identity;
		break;
	case PDF_ANNOT_HIGHLIGHT:
		pdf_write_highlight_appearance(ctx, annot, buf, rect, res);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_UNDERLINE:
		pdf_write_underline_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_STRIKE_OUT:
		pdf_write_strike_out_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_SQUIGGLY:
		pdf_write_squiggly_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_REDACT:
		pdf_write_redact_appearance(ctx, annot, buf, rect);
		*matrix = fz_identity;
		*bbox = *rect;
		break;
	case PDF_ANNOT_STAMP:
		pdf_write_stamp_appearance(ctx, annot, buf, rect, bbox, res);
		*matrix = fz_identity;
		break;
	case PDF_ANNOT_FREE_TEXT:
		pdf_write_free_text_appearance(ctx, annot, buf, rect, bbox, matrix, res);
		break;
	}
}