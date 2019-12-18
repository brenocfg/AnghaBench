#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mark {int /*<<< orphan*/  loc; } ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  q; int /*<<< orphan*/  text; int /*<<< orphan*/  p; } ;
struct TYPE_3__ {int key; scalar_t__ mod; int x; int y; TYPE_2__* focus; int /*<<< orphan*/  dialog; scalar_t__ plain; scalar_t__ right; scalar_t__ middle; scalar_t__ down; } ;

/* Variables and functions */
 int DEFRES ; 
 scalar_t__ GLUT_ACTIVE_ALT ; 
#define  KEY_DOWN 135 
#define  KEY_ESCAPE 134 
#define  KEY_F1 133 
 int KEY_F4 ; 
#define  KEY_LEFT 132 
#define  KEY_PAGE_DOWN 131 
#define  KEY_PAGE_UP 130 
#define  KEY_RIGHT 129 
#define  KEY_UP 128 
 int /*<<< orphan*/  auto_zoom () ; 
 int /*<<< orphan*/  auto_zoom_h () ; 
 int /*<<< orphan*/  auto_zoom_w () ; 
 int canvas_h ; 
 int canvas_w ; 
 int /*<<< orphan*/  clear_search () ; 
 int /*<<< orphan*/  ctx ; 
 int currentaa ; 
 int currenticc ; 
 int currentinvert ; 
 void* currentpage ; 
 int currentrotate ; 
 int currentseparations ; 
 int currenttint ; 
 int /*<<< orphan*/  currentzoom ; 
 int /*<<< orphan*/  do_save_pdf_file () ; 
 int /*<<< orphan*/  doc ; 
 scalar_t__ eqloc (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  future_count ; 
 void* fz_clamp_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fz_last_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_make_location (int,int) ; 
 int fz_maxi (int,int) ; 
 void* fz_next_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* fz_previous_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  glutLeaveMainLoop () ; 
 int /*<<< orphan*/  help_dialog ; 
 int /*<<< orphan*/  history_count ; 
 int /*<<< orphan*/  is_first_page (void*) ; 
 int /*<<< orphan*/  is_last_page (void*) ; 
 int /*<<< orphan*/  jump_to_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_to_page (int) ; 
 int layout_em ; 
 struct mark* marks ; 
 scalar_t__ nelem (struct mark*) ; 
 int number ; 
 int /*<<< orphan*/  pop_future () ; 
 int /*<<< orphan*/  pop_history () ; 
 int /*<<< orphan*/  push_history () ; 
 int /*<<< orphan*/  relayout () ; 
 int /*<<< orphan*/  reload () ; 
 int /*<<< orphan*/  restore_mark (struct mark) ; 
 struct mark save_mark () ; 
 int scroll_x ; 
 int scroll_y ; 
 int search_active ; 
 int search_dir ; 
 int /*<<< orphan*/  search_hit_page ; 
 TYPE_2__ search_input ; 
 int /*<<< orphan*/  search_needle ; 
 void* search_page ; 
 int /*<<< orphan*/ * selected_annot ; 
 int /*<<< orphan*/  set_zoom (int,int,int) ; 
 int showform ; 
 int showinfo ; 
 int showlinks ; 
 int showsearch ; 
 int /*<<< orphan*/  shrinkwrap () ; 
 int /*<<< orphan*/  smart_move_backward () ; 
 int /*<<< orphan*/  smart_move_forward () ; 
 int /*<<< orphan*/  toggle_annotate () ; 
 int /*<<< orphan*/  toggle_fullscreen () ; 
 int /*<<< orphan*/  toggle_outline () ; 
 TYPE_1__ ui ; 
 int zoom_in (int /*<<< orphan*/ ) ; 
 int zoom_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_app(void)
{
	if (ui.key == KEY_F4 && ui.mod == GLUT_ACTIVE_ALT)
		glutLeaveMainLoop();

	if (ui.down || ui.middle || ui.right || ui.key)
		showinfo = 0;

	if (!ui.focus && ui.key && ui.plain)
	{
		switch (ui.key)
		{
		case KEY_ESCAPE: clear_search(); selected_annot = NULL; break;
		case KEY_F1: ui.dialog = help_dialog; break;
		case 'a': toggle_annotate(); break;
		case 'o': toggle_outline(); break;
		case 'L': showlinks = !showlinks; break;
		case 'F': showform = !showform; break;
		case 'i': showinfo = !showinfo; break;
		case 'r': reload(); break;
		case 'q': glutLeaveMainLoop(); break;
		case 'S': do_save_pdf_file(); break;

		case '>': layout_em = number > 0 ? number : layout_em + 1; relayout(); break;
		case '<': layout_em = number > 0 ? number : layout_em - 1; relayout(); break;

		case 'C': currenttint = !currenttint; break;
		case 'I': currentinvert = !currentinvert; break;
		case 'e': currentseparations = !currentseparations; break;
		case 'E': currenticc = !currenticc; break;
		case 'f': toggle_fullscreen(); break;
		case 'w': shrinkwrap(); break;
		case 'W': auto_zoom_w(); break;
		case 'H': auto_zoom_h(); break;
		case 'Z': auto_zoom(); break;
		case 'z': set_zoom(number > 0 ? number : DEFRES, canvas_w/2, canvas_h/2); break;
		case '+': set_zoom(zoom_in(currentzoom), ui.x, ui.y); break;
		case '-': set_zoom(zoom_out(currentzoom), ui.x, ui.y); break;
		case '[': currentrotate -= 90; break;
		case ']': currentrotate += 90; break;
		case 'k': case KEY_UP: scroll_y -= 10; break;
		case 'j': case KEY_DOWN: scroll_y += 10; break;
		case 'h': case KEY_LEFT: scroll_x -= 10; break;
		case 'l': case KEY_RIGHT: scroll_x += 10; break;

		case 'b': number = fz_maxi(number, 1); while (number--) smart_move_backward(); break;
		case ' ': number = fz_maxi(number, 1); while (number--) smart_move_forward(); break;
		case 'g': jump_to_page(number - 1); break;
		case 'G': jump_to_location(fz_last_page(ctx, doc)); break;

		case ',': case KEY_PAGE_UP:
			number = fz_maxi(number, 1);
			while (number--)
				currentpage = fz_previous_page(ctx, doc, currentpage);
			break;
		case '.': case KEY_PAGE_DOWN:
			number = fz_maxi(number, 1);
			while (number--)
				currentpage = fz_next_page(ctx, doc, currentpage);
			break;

		case 'A':
			if (number == 0)
				currentaa = (currentaa == 8 ? 0 : 8);
			else
				currentaa = number;
			break;

		case 'm':
			if (number == 0)
				push_history();
			else if (number > 0 && number < (int)nelem(marks))
				marks[number] = save_mark();
			break;
		case 't':
			if (number == 0)
			{
				if (history_count > 0)
					pop_history();
			}
			else if (number > 0 && number < (int)nelem(marks))
			{
				struct mark mark = marks[number];
				restore_mark(mark);
				jump_to_location(mark.loc);
			}
			break;
		case 'T':
			if (number == 0)
			{
				if (future_count > 0)
					pop_future();
			}
			break;

		case '/':
			clear_search();
			search_dir = 1;
			showsearch = 1;
			ui.focus = &search_input;
			search_input.p = search_input.text;
			search_input.q = search_input.end;
			break;
		case '?':
			clear_search();
			search_dir = -1;
			showsearch = 1;
			ui.focus = &search_input;
			search_input.p = search_input.text;
			search_input.q = search_input.end;
			break;
		case 'N':
			search_dir = -1;
			search_active = !!search_needle;
			if (eqloc(search_hit_page, currentpage))
			{
				search_page = fz_previous_page(ctx, doc, currentpage);
				if (is_first_page(search_page))
					search_active = 0;
			}
			else
			{
				search_page = currentpage;
			}
			search_hit_page = fz_make_location(-1, -1);
			break;
		case 'n':
			search_dir = 1;
			search_active = !!search_needle;
			if (eqloc(search_hit_page, currentpage))
			{
				search_page = fz_next_page(ctx, doc, currentpage);
				if (is_last_page(search_page))
					search_active = 0;
			}
			else
			{
				search_page = currentpage;
			}
			search_hit_page = fz_make_location(-1, -1);
			break;
		}

		if (ui.key >= '0' && ui.key <= '9')
			number = number * 10 + ui.key - '0';
		else
			number = 0;

		currentpage = fz_clamp_location(ctx, doc, currentpage);
		while (currentrotate < 0) currentrotate += 360;
		while (currentrotate >= 360) currentrotate -= 360;

		if (!eqloc(search_hit_page, currentpage))
			search_hit_page = fz_make_location(-1, -1); /* clear highlights when navigating */

		ui.key = 0; /* we ate the key event, so zap it */
	}
}