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

/* Variables and functions */
#define  PDF_ANNOT_HIGHLIGHT 135 
#define  PDF_ANNOT_INK 134 
#define  PDF_ANNOT_POLYGON 133 
#define  PDF_ANNOT_POLY_LINE 132 
#define  PDF_ANNOT_REDACT 131 
#define  PDF_ANNOT_SQUIGGLY 130 
#define  PDF_ANNOT_STRIKE_OUT 129 
#define  PDF_ANNOT_UNDERLINE 128 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  getuser () ; 
 int is_draw_mode ; 
 int /*<<< orphan*/  page ; 
 scalar_t__ pdf_annot_has_author (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_create_annot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_set_annot_author (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_set_annot_modification_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_update_appearance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_page () ; 
 int /*<<< orphan*/  selected_annot ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void new_annot(int type)
{
	selected_annot = pdf_create_annot(ctx, page, type);

	pdf_set_annot_modification_date(ctx, selected_annot, time(NULL));
	if (pdf_annot_has_author(ctx, selected_annot))
		pdf_set_annot_author(ctx, selected_annot, getuser());

	pdf_update_appearance(ctx, selected_annot);

	switch (type)
	{
	case PDF_ANNOT_INK:
	case PDF_ANNOT_POLYGON:
	case PDF_ANNOT_POLY_LINE:
	case PDF_ANNOT_HIGHLIGHT:
	case PDF_ANNOT_UNDERLINE:
	case PDF_ANNOT_STRIKE_OUT:
	case PDF_ANNOT_SQUIGGLY:
	case PDF_ANNOT_REDACT:
		is_draw_mode = 1;
		break;
	}

	render_page();
}