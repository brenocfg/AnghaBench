#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_22__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_21__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_20__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_24__ {TYPE_4__ ll; TYPE_3__ lr; TYPE_2__ ur; TYPE_1__ ul; } ;
typedef  TYPE_5__ fz_quad ;
struct TYPE_25__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_6__ fz_point ;
struct TYPE_26__ {scalar_t__ mod; scalar_t__ right; int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_6__* active; TYPE_6__* hot; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_SELECT_LINES ; 
 int /*<<< orphan*/  FZ_SELECT_WORDS ; 
 scalar_t__ GLUT_ACTIVE_CTRL ; 
 scalar_t__ GLUT_ACTIVE_SHIFT ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_ONE_MINUS_DST_COLOR ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_ZERO ; 
 int /*<<< orphan*/  ctx ; 
 char* fz_copy_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__,TYPE_6__,int) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,char*) ; 
 int fz_highlight_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__,TYPE_6__,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_snap_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__ fz_transform_point (TYPE_6__,int /*<<< orphan*/ ) ; 
 TYPE_5__ fz_transform_quad (TYPE_5__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor4f (int,int,int,int) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glVertex2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nelem (TYPE_5__*) ; 
 int /*<<< orphan*/  page_text ; 
 TYPE_7__ ui ; 
 scalar_t__ ui_mouse_inside (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_set_clipboard (char*) ; 
 int /*<<< orphan*/  view_page_area ; 
 int /*<<< orphan*/  view_page_ctm ; 
 int /*<<< orphan*/  view_page_inv_ctm ; 

__attribute__((used)) static void do_page_selection(void)
{
	static fz_point pt = { 0, 0 };
	fz_quad hits[1000];
	int i, n;

	if (ui_mouse_inside(view_page_area))
	{
		ui.hot = &pt;
		if (!ui.active && ui.right)
		{
			ui.active = &pt;
			pt.x = ui.x;
			pt.y = ui.y;
		}
	}

	if (ui.active == &pt)
	{
		fz_point page_a = { pt.x, pt.y };
		fz_point page_b = { ui.x, ui.y };

		page_a = fz_transform_point(page_a, view_page_inv_ctm);
		page_b = fz_transform_point(page_b, view_page_inv_ctm);

		if (ui.mod == GLUT_ACTIVE_CTRL)
			fz_snap_selection(ctx, page_text, &page_a, &page_b, FZ_SELECT_WORDS);
		else if (ui.mod == GLUT_ACTIVE_CTRL + GLUT_ACTIVE_SHIFT)
			fz_snap_selection(ctx, page_text, &page_a, &page_b, FZ_SELECT_LINES);

		n = fz_highlight_selection(ctx, page_text, page_a, page_b, hits, nelem(hits));

		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); /* invert destination color */
		glEnable(GL_BLEND);

		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
		for (i = 0; i < n; ++i)
		{
			fz_quad thit = fz_transform_quad(hits[i], view_page_ctm);
			glVertex2f(thit.ul.x, thit.ul.y);
			glVertex2f(thit.ur.x, thit.ur.y);
			glVertex2f(thit.lr.x, thit.lr.y);
			glVertex2f(thit.ll.x, thit.ll.y);
		}
		glEnd();

		glDisable(GL_BLEND);

		if (!ui.right)
		{
			char *s;
#ifdef _WIN32
			s = fz_copy_selection(ctx, page_text, page_a, page_b, 1);
#else
			s = fz_copy_selection(ctx, page_text, page_a, page_b, 0);
#endif
			ui_set_clipboard(s);
			fz_free(ctx, s);
		}
	}
}