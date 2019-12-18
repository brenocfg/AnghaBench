#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ x0; scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; } ;
typedef  TYPE_1__ fz_irect ;
struct TYPE_25__ {int /*<<< orphan*/  page; int /*<<< orphan*/  chapter; } ;
struct TYPE_24__ {scalar_t__ window_h; scalar_t__ hot; scalar_t__ active; int x; int y; scalar_t__ mod; int scroll_x; int lineheight; int scroll_y; scalar_t__ gridsize; TYPE_6__* focus; scalar_t__ middle; } ;
struct TYPE_23__ {scalar_t__ w; scalar_t__ h; } ;
struct TYPE_22__ {scalar_t__ end; scalar_t__ text; } ;
struct TYPE_21__ {int e; int f; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  E ; 
 scalar_t__ GLUT_ACTIVE_CTRL ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  L ; 
 int /*<<< orphan*/  N ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  NW ; 
 int /*<<< orphan*/  T ; 
 scalar_t__ UI_INPUT_ACCEPT ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  X ; 
 scalar_t__ canvas_h ; 
 scalar_t__ canvas_w ; 
 scalar_t__ canvas_x ; 
 scalar_t__ canvas_y ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_9__ currentpage ; 
 int /*<<< orphan*/  currentzoom ; 
 int /*<<< orphan*/  do_annotate_canvas (TYPE_1__) ; 
 int /*<<< orphan*/  do_links (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_page_selection () ; 
 int /*<<< orphan*/  do_search_hits () ; 
 int /*<<< orphan*/  do_widget_canvas (TYPE_1__) ; 
 scalar_t__ doc ; 
 TYPE_2__ draw_page_ctm ; 
 scalar_t__ eqloc (int /*<<< orphan*/ ,TYPE_9__) ; 
 int fz_clamp (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_invert_matrix (TYPE_2__) ; 
 int /*<<< orphan*/  fz_irect_from_rect (int /*<<< orphan*/ ) ; 
 TYPE_9__ fz_make_location (int,int) ; 
 int /*<<< orphan*/ * fz_strdup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glScissor (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  page_bounds ; 
 TYPE_7__ page_tex ; 
 scalar_t__ pdf ; 
 int /*<<< orphan*/  render_page_if_changed () ; 
 int scroll_x ; 
 int scroll_y ; 
 int search_active ; 
 scalar_t__ search_hit_count ; 
 int /*<<< orphan*/  search_hit_page ; 
 TYPE_6__ search_input ; 
 int /*<<< orphan*/ * search_needle ; 
 TYPE_9__ search_page ; 
 int /*<<< orphan*/  set_zoom (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ showsearch ; 
 int /*<<< orphan*/ * tooltip ; 
 TYPE_8__ ui ; 
 int /*<<< orphan*/  ui_draw_image (TYPE_7__*,int,int) ; 
 scalar_t__ ui_input (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_label (char*,...) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ui_mouse_inside (TYPE_1__) ; 
 TYPE_1__ ui_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_pack_pop () ; 
 int /*<<< orphan*/  ui_pack_push (TYPE_1__) ; 
 int /*<<< orphan*/  ui_panel_begin (int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  ui_panel_end () ; 
 int /*<<< orphan*/  view_page_area ; 
 int /*<<< orphan*/  view_page_bounds ; 
 TYPE_2__ view_page_ctm ; 
 int /*<<< orphan*/  view_page_inv_ctm ; 
 int /*<<< orphan*/  zoom_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zoom_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_canvas(void)
{
	static int saved_scroll_x = 0;
	static int saved_scroll_y = 0;
	static int saved_ui_x = 0;
	static int saved_ui_y = 0;
	fz_irect area;
	int page_x, page_y;

	tooltip = NULL;

	ui_layout(ALL, BOTH, NW, 0, 0);
	ui_pack_push(area = ui_pack(0, 0));
	glScissor(area.x0, ui.window_h-area.y1, area.x1-area.x0, area.y1-area.y0);
	glEnable(GL_SCISSOR_TEST);

	canvas_x = area.x0;
	canvas_y = area.y0;
	canvas_w = area.x1 - area.x0;
	canvas_h = area.y1 - area.y0;

	if (ui_mouse_inside(area))
	{
		ui.hot = doc;
		if (!ui.active && ui.middle)
		{
			ui.active = doc;
			saved_scroll_x = scroll_x;
			saved_scroll_y = scroll_y;
			saved_ui_x = ui.x;
			saved_ui_y = ui.y;
		}
	}

	if (ui.hot == doc)
	{
		if (ui.mod == 0)
		{
			scroll_x -= ui.scroll_x * ui.lineheight * 3;
			scroll_y -= ui.scroll_y * ui.lineheight * 3;
		}
		else if (ui.mod == GLUT_ACTIVE_CTRL)
		{
			if (ui.scroll_y > 0) set_zoom(zoom_in(currentzoom), ui.x, ui.y);
			if (ui.scroll_y < 0) set_zoom(zoom_out(currentzoom), ui.x, ui.y);
		}
	}

	render_page_if_changed();

	if (ui.active == doc)
	{
		scroll_x = saved_scroll_x + saved_ui_x - ui.x;
		scroll_y = saved_scroll_y + saved_ui_y - ui.y;
	}

	if (page_tex.w <= canvas_w)
	{
		scroll_x = 0;
		page_x = canvas_x + (canvas_w - page_tex.w) / 2;
	}
	else
	{
		scroll_x = fz_clamp(scroll_x, 0, page_tex.w - canvas_w);
		page_x = canvas_x - scroll_x;
	}

	if (page_tex.h <= canvas_h)
	{
		scroll_y = 0;
		page_y = canvas_y + (canvas_h - page_tex.h) / 2;
	}
	else
	{
		scroll_y = fz_clamp(scroll_y, 0, page_tex.h - canvas_h);
		page_y = canvas_y - scroll_y;
	}

	view_page_ctm = draw_page_ctm;
	view_page_ctm.e += page_x;
	view_page_ctm.f += page_y;
	view_page_inv_ctm = fz_invert_matrix(view_page_ctm);
	view_page_bounds = fz_transform_rect(page_bounds, view_page_ctm);
	view_page_area = fz_irect_from_rect(view_page_bounds);

	ui_draw_image(&page_tex, page_x, page_y);

	if (search_active)
	{
		ui_layout(T, X, NW, 0, 0);
		ui_panel_begin(0, ui.gridsize+8, 4, 4, 1);
		ui_layout(L, NONE, W, 2, 0);
		ui_label("Searching chapter %d page %d...", search_page.chapter, search_page.page);
		ui_panel_end();
	}
	else
	{
		if (pdf)
		{
			do_annotate_canvas(area);
			do_widget_canvas(area);
		}
		do_links(links);
		do_page_selection();

		if (eqloc(search_hit_page, currentpage) && search_hit_count > 0)
			do_search_hits();
	}

	if (showsearch)
	{
		ui_layout(T, X, NW, 0, 0);
		ui_panel_begin(0, ui.gridsize+8, 4, 4, 1);
		ui_layout(L, NONE, W, 2, 0);
		ui_label("Search:");
		ui_layout(ALL, X, E, 2, 0);
		if (ui_input(&search_input, 0, 1) == UI_INPUT_ACCEPT)
		{
			showsearch = 0;
			search_page = fz_make_location(-1, -1);
			if (search_needle)
			{
				fz_free(ctx, search_needle);
				search_needle = NULL;
			}
			if (search_input.end > search_input.text)
			{
				search_needle = fz_strdup(ctx, search_input.text);
				search_active = 1;
				search_page = currentpage;
			}
		}
		if (ui.focus != &search_input)
			showsearch = 0;
		ui_panel_end();
	}

	if (tooltip)
	{
		ui_layout(B, X, N, 0, 0);
		ui_panel_begin(0, ui.gridsize, 4, 4, 1);
		ui_layout(L, NONE, W, 2, 0);
		ui_label("%s", tooltip);
		ui_panel_end();
	}

	ui_pack_pop();
	glDisable(GL_SCISSOR_TEST);
}