#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_page ;
struct TYPE_20__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ pdf_annot ;
struct TYPE_21__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_3__ fz_rect ;
struct TYPE_22__ {int member_0; int member_1; } ;
typedef  TYPE_4__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  enum pdf_annot_type { ____Placeholder_pdf_annot_type } pdf_annot_type ;

/* Variables and functions */
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  P ; 
#define  PDF_ANNOT_CARET 143 
#define  PDF_ANNOT_CIRCLE 142 
#define  PDF_ANNOT_FILE_ATTACHMENT 141 
#define  PDF_ANNOT_FREE_TEXT 140 
#define  PDF_ANNOT_HIGHLIGHT 139 
#define  PDF_ANNOT_INK 138 
 int PDF_ANNOT_IS_NO_ROTATE ; 
 int PDF_ANNOT_IS_NO_ZOOM ; 
 int PDF_ANNOT_IS_PRINT ; 
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
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rotate ; 
 TYPE_2__* pdf_create_annot_raw (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* pdf_keep_annot (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_set_annot_border (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pdf_set_annot_color (int /*<<< orphan*/ *,TYPE_2__*,int,float const*) ; 
 int /*<<< orphan*/  pdf_set_annot_default_appearance (int /*<<< orphan*/ *,TYPE_2__*,char*,int,float const*) ; 
 int /*<<< orphan*/  pdf_set_annot_line (int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__,TYPE_4__) ; 
 int /*<<< orphan*/  pdf_set_annot_rect (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

pdf_annot *
pdf_create_annot(fz_context *ctx, pdf_page *page, enum pdf_annot_type type)
{
	static const float black[3] = { 0, 0, 0 };
	static const float red[3] = { 1, 0, 0 };
	static const float green[3] = { 0, 1, 0 };
	static const float blue[3] = { 0, 0, 1 };
	static const float yellow[3] = { 1, 1, 0 };
	static const float magenta[3] = { 1, 0, 1 };

	int flags = PDF_ANNOT_IS_PRINT; /* Make printable as default */

	pdf_annot *annot = pdf_create_annot_raw(ctx, page, type);

	switch (type)
	{
	default:
		break;

	case PDF_ANNOT_TEXT:
	case PDF_ANNOT_FILE_ATTACHMENT:
	case PDF_ANNOT_SOUND:
		{
			fz_rect icon_rect = { 12, 12, 12+20, 12+20 };
			flags = PDF_ANNOT_IS_PRINT | PDF_ANNOT_IS_NO_ZOOM | PDF_ANNOT_IS_NO_ROTATE;
			pdf_set_annot_rect(ctx, annot, icon_rect);
			pdf_set_annot_color(ctx, annot, 3, yellow);
		}
		break;

	case PDF_ANNOT_FREE_TEXT:
		{
			fz_rect text_rect = { 12, 12, 12+200, 12+100 };

			/* Use undocumented Adobe property to match page rotation. */
			int rot = pdf_to_int(ctx, pdf_dict_get_inheritable(ctx, page->obj, PDF_NAME(Rotate)));
			if (rot != 0)
				pdf_dict_put_int(ctx, annot->obj, PDF_NAME(Rotate), rot);

			pdf_set_annot_rect(ctx, annot, text_rect);
			pdf_set_annot_border(ctx, annot, 0);
			pdf_set_annot_default_appearance(ctx, annot, "Helv", 12, black);
		}
		break;

	case PDF_ANNOT_STAMP:
		{
			fz_rect stamp_rect = { 12, 12, 12+190, 12+50 };
			pdf_set_annot_rect(ctx, annot, stamp_rect);
			pdf_set_annot_color(ctx, annot, 3, red);
		}
		break;

	case PDF_ANNOT_CARET:
		{
			fz_rect caret_rect = { 12, 12, 12+18, 12+15 };
			pdf_set_annot_rect(ctx, annot, caret_rect);
			pdf_set_annot_color(ctx, annot, 3, blue);
		}
		break;

	case PDF_ANNOT_LINE:
		{
			fz_point a = { 12, 12 }, b = { 12 + 100, 12 + 50 };
			pdf_set_annot_line(ctx, annot, a, b);
			pdf_set_annot_border(ctx, annot, 1);
			pdf_set_annot_color(ctx, annot, 3, red);
		}
		break;

	case PDF_ANNOT_SQUARE:
	case PDF_ANNOT_CIRCLE:
		{
			fz_rect shape_rect = { 12, 12, 12+100, 12+50 };
			pdf_set_annot_rect(ctx, annot, shape_rect);
			pdf_set_annot_border(ctx, annot, 1);
			pdf_set_annot_color(ctx, annot, 3, red);
		}
		break;

	case PDF_ANNOT_POLYGON:
	case PDF_ANNOT_POLY_LINE:
	case PDF_ANNOT_INK:
		pdf_set_annot_border(ctx, annot, 1);
		pdf_set_annot_color(ctx, annot, 3, red);
		break;

	case PDF_ANNOT_HIGHLIGHT:
		pdf_set_annot_color(ctx, annot, 3, yellow);
		break;
	case PDF_ANNOT_UNDERLINE:
		pdf_set_annot_color(ctx, annot, 3, green);
		break;
	case PDF_ANNOT_STRIKE_OUT:
		pdf_set_annot_color(ctx, annot, 3, red);
		break;
	case PDF_ANNOT_SQUIGGLY:
		pdf_set_annot_color(ctx, annot, 3, magenta);
		break;
	}

	pdf_dict_put(ctx, annot->obj, PDF_NAME(P), page->obj);
	pdf_dict_put_int(ctx, annot->obj, PDF_NAME(F), flags);

	return pdf_keep_annot(ctx, annot);
}