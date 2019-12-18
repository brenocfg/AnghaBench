#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* search; int pageno; int searchpage; int pagecount; scalar_t__ hit_count; int /*<<< orphan*/  hit_bbox; int /*<<< orphan*/  page_text; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  enum panning { ____Placeholder_panning } panning ;

/* Variables and functions */
 int /*<<< orphan*/  HAND ; 
 int PAN_TO_BOTTOM ; 
 int PAN_TO_TOP ; 
 int /*<<< orphan*/  WAIT ; 
 scalar_t__ fz_search_stext_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdfapp_showpage (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdfapp_warn (TYPE_1__*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  wincursor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winrepaint (TYPE_1__*) ; 

__attribute__((used)) static void pdfapp_search_in_direction(pdfapp_t *app, enum panning *panto, int dir)
{
	int firstpage, page;

	/* abort if no search string */
	if (app->search[0] == 0)
	{
		winrepaint(app);
		return;
	}

	wincursor(app, WAIT);

	firstpage = app->pageno;
	if (app->searchpage == app->pageno)
		page = app->pageno + dir;
	else
		page = app->pageno;

	if (page < 1) page = app->pagecount;
	if (page > app->pagecount) page = 1;

	do
	{
		if (page != app->pageno)
		{
			app->pageno = page;
			pdfapp_showpage(app, 1, 0, 0, 0, 1);
		}

		app->hit_count = fz_search_stext_page(app->ctx, app->page_text, app->search, app->hit_bbox, nelem(app->hit_bbox));
		if (app->hit_count > 0)
		{
			*panto = dir == 1 ? PAN_TO_TOP : PAN_TO_BOTTOM;
			app->searchpage = app->pageno;
			wincursor(app, HAND);
			winrepaint(app);
			return;
		}

		page += dir;
		if (page < 1) page = app->pagecount;
		if (page > app->pagecount) page = 1;
	} while (page != firstpage);

	pdfapp_warn(app, "String '%s' not found.", app->search);

	app->pageno = firstpage;
	pdfapp_showpage(app, 1, 0, 0, 0, 0);
	wincursor(app, HAND);
	winrepaint(app);
}