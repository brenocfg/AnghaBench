#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ pdf_page ;
struct TYPE_8__ {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_2__ fz_irect ;
struct TYPE_10__ {int /*<<< orphan*/  page; int /*<<< orphan*/  chapter; } ;
struct TYPE_9__ {scalar_t__ h; scalar_t__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_SEPARATION_COMPOSITE ; 
 scalar_t__ PDF_ANNOT_WIDGET ; 
 int /*<<< orphan*/  ctx ; 
 scalar_t__ currenticc ; 
 TYPE_6__ currentpage ; 
 scalar_t__ currentseparations ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  draw_page_bounds ; 
 int /*<<< orphan*/  fz_bound_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fz_count_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_disable_icc (int /*<<< orphan*/ ) ; 
 scalar_t__ fz_document_output_intent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stext_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_enable_icc (int /*<<< orphan*/ ) ; 
 TYPE_2__ fz_irect_from_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_load_chapter_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_load_links (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_new_stext_page_from_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_page_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_page_uses_overprint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_set_separation_behavior (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fzpage ; 
 int /*<<< orphan*/ * links ; 
 TYPE_1__* page ; 
 int /*<<< orphan*/  page_bounds ; 
 TYPE_3__ page_tex ; 
 int /*<<< orphan*/ * page_text ; 
 scalar_t__ pdf ; 
 int /*<<< orphan*/  pdf_annot_event_blur (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_annot_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * selected_annot ; 
 int /*<<< orphan*/ * seps ; 
 int /*<<< orphan*/  transform_page () ; 

void load_page(void)
{
	fz_irect area;

	/* clear all editor selections */
	if (selected_annot && pdf_annot_type(ctx, selected_annot) == PDF_ANNOT_WIDGET)
		pdf_annot_event_blur(ctx, selected_annot);
	selected_annot = NULL;

	fz_drop_stext_page(ctx, page_text);
	page_text = NULL;
	fz_drop_separations(ctx, seps);
	seps = NULL;
	fz_drop_link(ctx, links);
	links = NULL;
	fz_drop_page(ctx, fzpage);
	fzpage = NULL;

	fzpage = fz_load_chapter_page(ctx, doc, currentpage.chapter, currentpage.page);
	if (pdf)
		page = (pdf_page*)fzpage;

	links = fz_load_links(ctx, fzpage);
	page_text = fz_new_stext_page_from_page(ctx, fzpage, NULL);

	if (currenticc)
		fz_enable_icc(ctx);
	else
		fz_disable_icc(ctx);

	if (currentseparations)
	{
		seps = fz_page_separations(ctx, &page->super);
		if (seps)
		{
			int i, n = fz_count_separations(ctx, seps);
			for (i = 0; i < n; i++)
				fz_set_separation_behavior(ctx, seps, i, FZ_SEPARATION_COMPOSITE);
		}
		else if (fz_page_uses_overprint(ctx, &page->super))
			seps = fz_new_separations(ctx, 0);
		else if (fz_document_output_intent(ctx, doc))
			seps = fz_new_separations(ctx, 0);
	}

	/* compute bounds here for initial window size */
	page_bounds = fz_bound_page(ctx, fzpage);
	transform_page();

	area = fz_irect_from_rect(draw_page_bounds);
	page_tex.w = area.x1 - area.x0;
	page_tex.h = area.y1 - area.y0;
}