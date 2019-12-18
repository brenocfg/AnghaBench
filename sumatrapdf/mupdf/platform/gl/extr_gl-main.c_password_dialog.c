#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int gridsize; scalar_t__ key; int /*<<< orphan*/ * dialog; int /*<<< orphan*/  focus; } ;
struct TYPE_4__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  B ; 
 scalar_t__ KEY_ESCAPE ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  NW ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  T ; 
 int UI_INPUT_ACCEPT ; 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/  glutLeaveMainLoop () ; 
 TYPE_1__ input_password ; 
 int /*<<< orphan*/  password ; 
 int /*<<< orphan*/  reload () ; 
 int /*<<< orphan*/  shrinkwrap () ; 
 TYPE_2__ ui ; 
 scalar_t__ ui_button (char*) ; 
 int /*<<< orphan*/  ui_dialog_begin (int,int) ; 
 int /*<<< orphan*/  ui_dialog_end () ; 
 int ui_input (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ui_label (char*) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_panel_begin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_panel_end () ; 
 int /*<<< orphan*/  ui_spacer () ; 

__attribute__((used)) static void password_dialog(void)
{
	int is;
	ui_dialog_begin(400, (ui.gridsize+4)*3);
	{
		ui_layout(T, X, NW, 2, 2);
		ui_label("Password:");
		is = ui_input(&input_password, 200, 1);

		ui_layout(B, X, NW, 2, 2);
		ui_panel_begin(0, ui.gridsize, 0, 0, 0);
		{
			ui_layout(R, NONE, S, 0, 0);
			if (ui_button("Cancel") || (!ui.focus && ui.key == KEY_ESCAPE))
				glutLeaveMainLoop();
			ui_spacer();
			if (ui_button("Okay") || is == UI_INPUT_ACCEPT)
			{
				password = input_password.text;
				ui.dialog = NULL;
				reload();
				shrinkwrap();
			}
		}
		ui_panel_end();
	}
	ui_dialog_end();
}