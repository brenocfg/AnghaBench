#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  page; int /*<<< orphan*/  obj; } ;
struct TYPE_7__ {int gridsize; int lineheight; scalar_t__ key; int /*<<< orphan*/ * dialog; int /*<<< orphan*/  focus; } ;
struct TYPE_6__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  B ; 
 scalar_t__ KEY_ESCAPE ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  NW ; 
 int PDF_TX_FIELD_IS_MULTILINE ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  T ; 
 int UI_INPUT_ACCEPT ; 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/  ctx ; 
 int pdf_field_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pdf_field_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_set_text_field_value (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_update_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_page () ; 
 TYPE_1__ tx_input ; 
 TYPE_3__* tx_widget ; 
 TYPE_2__ ui ; 
 int ui_break_lines (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ui_button (char*) ; 
 int /*<<< orphan*/  ui_dialog_begin (int,int) ; 
 int /*<<< orphan*/  ui_dialog_end () ; 
 int ui_input (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ui_label (char*,char const*) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_panel_begin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_panel_end () ; 
 int /*<<< orphan*/  ui_spacer () ; 

__attribute__((used)) static void tx_dialog(void)
{
	int ff = pdf_field_flags(ctx, tx_widget->obj);
	const char *label = pdf_field_label(ctx, tx_widget->obj);
	int tx_h = (ff & PDF_TX_FIELD_IS_MULTILINE) ? 10 : 1;
	int lbl_h = ui_break_lines((char*)label, NULL, 20, 394, NULL);
	int is;

	ui_dialog_begin(400, (ui.gridsize+4)*3 + ui.lineheight*(tx_h+lbl_h-2));
	{
		ui_layout(T, X, NW, 2, 2);
		ui_label("%s", label);
		is = ui_input(&tx_input, 200, tx_h);

		ui_layout(B, X, NW, 2, 2);
		ui_panel_begin(0, ui.gridsize, 0, 0, 0);
		{
			ui_layout(R, NONE, S, 0, 0);
			if (ui_button("Cancel") || (!ui.focus && ui.key == KEY_ESCAPE))
				ui.dialog = NULL;
			ui_spacer();
			if (ui_button("Okay") || is == UI_INPUT_ACCEPT)
			{
				pdf_set_text_field_value(ctx, tx_widget, tx_input.text);
				if (pdf_update_page(ctx, tx_widget->page))
					render_page();
				ui.dialog = NULL;
			}
		}
		ui_panel_end();
	}
	ui_dialog_end();
}