#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ key; int /*<<< orphan*/ * dialog; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  CENTER ; 
 int /*<<< orphan*/  FZ_VERSION ; 
 scalar_t__ KEY_ENTER ; 
 scalar_t__ KEY_ESCAPE ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/  help_dialog_text ; 
 TYPE_1__ ui ; 
 scalar_t__ ui_button (char*) ; 
 int /*<<< orphan*/  ui_dialog_begin (int,int) ; 
 int /*<<< orphan*/  ui_dialog_end () ; 
 int /*<<< orphan*/  ui_label (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_label_with_scrollbar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_spacer () ; 

__attribute__((used)) static void help_dialog(void)
{
	static int scroll;
	ui_dialog_begin(500, 1000);
	ui_layout(T, X, W, 2, 2);
	ui_label("MuPDF %s", FZ_VERSION);
	ui_spacer();
	ui_layout(B, NONE, S, 2, 2);
	if (ui_button("Okay") || ui.key == KEY_ENTER || ui.key == KEY_ESCAPE)
		ui.dialog = NULL;
	ui_spacer();
	ui_layout(ALL, BOTH, CENTER, 2, 2);
	ui_label_with_scrollbar(help_dialog_text, 0, 0, &scroll);
	ui_dialog_end();
}