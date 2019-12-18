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
 int /*<<< orphan*/  L ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  NW ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  do_clear_signature () ; 
 char* pdf_field_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_signature_error_description (scalar_t__) ; 
 scalar_t__ sig_cert_error ; 
 int /*<<< orphan*/  sig_designated_name ; 
 scalar_t__ sig_digest_error ; 
 scalar_t__ sig_subsequent_edits ; 
 TYPE_2__* sig_widget ; 
 TYPE_1__ ui ; 
 scalar_t__ ui_button (char*) ; 
 int /*<<< orphan*/  ui_dialog_begin (int,int) ; 
 int /*<<< orphan*/  ui_dialog_end () ; 
 int /*<<< orphan*/  ui_label (char*,...) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_panel_begin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_panel_end () ; 
 int /*<<< orphan*/  ui_spacer () ; 

__attribute__((used)) static void sig_verify_dialog(void)
{
	const char *label = pdf_field_label(ctx, sig_widget->obj);

	ui_dialog_begin(400, (ui.gridsize+4)*3 + ui.lineheight*10);
	{
		ui_layout(T, X, NW, 2, 2);

		ui_label("%s", label);
		ui_spacer();

		ui_label("Designated name: %s.", sig_designated_name);
		ui_spacer();

		if (sig_cert_error)
			ui_label("Certificate error: %s", pdf_signature_error_description(sig_cert_error));
		else
			ui_label("Certificate is trusted.");

		ui_spacer();

		if (sig_digest_error)
			ui_label("Digest error: %s", pdf_signature_error_description(sig_digest_error));
		else if (sig_subsequent_edits)
			ui_label("The signature is valid but there have been edits since signing.");
		else
			ui_label("The document is unchanged since signing.");

		ui_layout(B, X, NW, 2, 2);
		ui_panel_begin(0, ui.gridsize, 0, 0, 0);
		{
			ui_layout(L, NONE, S, 0, 0);
			if (ui_button("Clear"))
			{
				ui.dialog = NULL;
				do_clear_signature();
			}
			ui_layout(R, NONE, S, 0, 0);
			if (ui_button("Close") || (!ui.focus && ui.key == KEY_ESCAPE))
				ui.dialog = NULL;
		}
		ui_panel_end();
	}
	ui_dialog_end();
}