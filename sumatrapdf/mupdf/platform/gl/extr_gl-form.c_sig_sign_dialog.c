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
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
struct TYPE_3__ {int gridsize; int lineheight; scalar_t__ key; int /*<<< orphan*/ * dialog; int /*<<< orphan*/  focus; } ;

/* Variables and functions */
 int /*<<< orphan*/  B ; 
 scalar_t__ KEY_ESCAPE ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  NW ; 
 int PDF_FIELD_IS_READ_ONLY ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/ * cert_file_dialog ; 
 int /*<<< orphan*/  cert_file_filter ; 
 int /*<<< orphan*/  cert_filename ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fz_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pdf_field_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pdf_field_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* sig_widget ; 
 TYPE_1__ ui ; 
 scalar_t__ ui_button (char*) ; 
 int /*<<< orphan*/  ui_dialog_begin (int,int) ; 
 int /*<<< orphan*/  ui_dialog_end () ; 
 int /*<<< orphan*/  ui_init_open_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_label (char*,...) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_panel_begin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_panel_end () ; 
 int /*<<< orphan*/  ui_spacer () ; 

__attribute__((used)) static void sig_sign_dialog(void)
{
	const char *label = pdf_field_label(ctx, sig_widget->obj);

	ui_dialog_begin(400, (ui.gridsize+4)*3 + ui.lineheight*10);
	{
		ui_layout(T, X, NW, 2, 2);

		ui_label("%s", label);
		ui_spacer();

		ui_label("Would you like to sign this field?");

		ui_layout(B, X, NW, 2, 2);
		ui_panel_begin(0, ui.gridsize, 0, 0, 0);
		{
			ui_layout(R, NONE, S, 0, 0);
			if (ui_button("Cancel") || (!ui.focus && ui.key == KEY_ESCAPE))
				ui.dialog = NULL;
			ui_spacer();
			if (!(pdf_field_flags(ctx, sig_widget->obj) & PDF_FIELD_IS_READ_ONLY))
			{
				if (ui_button("Sign"))
				{
					fz_strlcpy(cert_filename, filename, sizeof cert_filename);
					ui_init_open_file(".", cert_file_filter);
					ui.dialog = cert_file_dialog;
				}
			}
		}
		ui_panel_end();
	}
	ui_dialog_end();
}