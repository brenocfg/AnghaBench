#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct input {int /*<<< orphan*/  text; } ;
typedef  int /*<<< orphan*/  pdf_annot ;

/* Variables and functions */
 scalar_t__ UI_INPUT_EDIT ; 
 int /*<<< orphan*/  ctx ; 
 char* pdf_annot_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_set_annot_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * selected_annot ; 
 scalar_t__ ui_input (struct input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_input_init (struct input*,char const*) ; 
 int /*<<< orphan*/  ui_label (char*) ; 

__attribute__((used)) static void do_annotate_contents(void)
{
	static pdf_annot *last_annot = NULL;
	static struct input input;
	const char *contents;

	if (selected_annot != last_annot)
	{
		last_annot = selected_annot;
		contents = pdf_annot_contents(ctx, selected_annot);
		ui_input_init(&input, contents);
	}

	ui_label("Contents:");
	if (ui_input(&input, 0, 5) >= UI_INPUT_EDIT)
		pdf_set_annot_contents(ctx, selected_annot, input.text);
}