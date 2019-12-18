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
struct TYPE_2__ {int /*<<< orphan*/  dialog; } ;

/* Variables and functions */
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  init_save_pdf_options () ; 
 scalar_t__ pdf ; 
 int /*<<< orphan*/  pdf_filter ; 
 int /*<<< orphan*/  save_pdf_dialog ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_init_save_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_save_pdf_file(void)
{
	if (pdf)
	{
		init_save_pdf_options();
		ui_init_save_file(filename, pdf_filter);
		ui.dialog = save_pdf_dialog;
	}
}