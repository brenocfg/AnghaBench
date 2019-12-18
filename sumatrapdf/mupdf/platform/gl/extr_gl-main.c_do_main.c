#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  page; int /*<<< orphan*/  chapter; } ;
struct TYPE_11__ {scalar_t__ key; scalar_t__ mod; scalar_t__ plain; scalar_t__ right; scalar_t__ middle; scalar_t__ down; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  GLUT_ELAPSED_TIME ; 
 scalar_t__ KEY_ESCAPE ; 
 int /*<<< orphan*/  NW ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  annotate_w ; 
 int /*<<< orphan*/  ctx ; 
 scalar_t__ currenticc ; 
 int /*<<< orphan*/  currentpage ; 
 scalar_t__ currentseparations ; 
 int /*<<< orphan*/  do_annotate_panel () ; 
 int /*<<< orphan*/  do_app () ; 
 int /*<<< orphan*/  do_canvas () ; 
 int /*<<< orphan*/  do_info () ; 
 int /*<<< orphan*/  do_outline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  eqloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fz_next_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__) ; 
 TYPE_2__ fz_previous_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__) ; 
 scalar_t__ fz_search_chapter_page_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int glutGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutPostRedisplay () ; 
 scalar_t__ is_first_page (TYPE_2__) ; 
 scalar_t__ is_last_page (TYPE_2__) ; 
 int /*<<< orphan*/  jump_to_location (TYPE_2__) ; 
 int /*<<< orphan*/  load_page () ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 
 scalar_t__ oldicc ; 
 int /*<<< orphan*/  oldpage ; 
 scalar_t__ oldseparations ; 
 int /*<<< orphan*/  outline ; 
 scalar_t__ search_active ; 
 scalar_t__ search_dir ; 
 scalar_t__ search_hit_count ; 
 TYPE_2__ search_hit_page ; 
 int /*<<< orphan*/  search_hit_quads ; 
 int /*<<< orphan*/  search_needle ; 
 TYPE_2__ search_page ; 
 scalar_t__ showannotate ; 
 scalar_t__ showinfo ; 
 scalar_t__ showoutline ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_panel_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ui_panel_end () ; 
 int /*<<< orphan*/  update_title () ; 

void do_main(void)
{
	if (search_active)
	{
		int start_time = glutGet(GLUT_ELAPSED_TIME);

		if (ui.key == KEY_ESCAPE)
			search_active = 0;

		/* ignore events during search */
		ui.key = ui.mod = ui.plain = 0;
		ui.down = ui.middle = ui.right = 0;

		while (search_active && glutGet(GLUT_ELAPSED_TIME) < start_time + 200)
		{
			search_hit_count = fz_search_chapter_page_number(ctx, doc,
				search_page.chapter, search_page.page,
				search_needle,
				search_hit_quads, nelem(search_hit_quads));
			if (search_hit_count)
			{
				search_active = 0;
				search_hit_page = search_page;
				jump_to_location(search_hit_page);
			}
			else
			{
				if (search_dir > 0)
				{
					if (is_last_page(search_page))
						search_active = 0;
					else
						search_page = fz_next_page(ctx, doc, search_page);
				}
				else
				{
					if (is_first_page(search_page))
						search_active = 0;
					else
						search_page = fz_previous_page(ctx, doc, search_page);
				}
			}
		}

		/* keep searching later */
		if (search_active)
			glutPostRedisplay();
	}

	do_app();

	if (showoutline)
		do_outline(outline);

	if (!eqloc(oldpage, currentpage) || oldseparations != currentseparations || oldicc != currenticc)
	{
		load_page();
		update_title();
	}

	if (showannotate)
	{
		ui_layout(R, BOTH, NW, 0, 0);
		ui_panel_begin(annotate_w, 0, 4, 4, 1);
		do_annotate_panel();
		ui_panel_end();
	}

	do_canvas();

	if (showinfo)
		do_info();
}