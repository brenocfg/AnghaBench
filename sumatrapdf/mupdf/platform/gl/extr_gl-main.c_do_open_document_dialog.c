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
struct TYPE_2__ {int /*<<< orphan*/ * dialog; } ;

/* Variables and functions */
 scalar_t__ doc ; 
 scalar_t__* filename ; 
 int /*<<< orphan*/  glutLeaveMainLoop () ; 
 int /*<<< orphan*/  load_document () ; 
 int /*<<< orphan*/  load_page () ; 
 int /*<<< orphan*/  render_page () ; 
 int /*<<< orphan*/  shrinkwrap () ; 
 TYPE_1__ ui ; 
 scalar_t__ ui_open_file (scalar_t__*) ; 
 int /*<<< orphan*/  update_title () ; 

__attribute__((used)) static void do_open_document_dialog(void)
{
	if (ui_open_file(filename))
	{
		ui.dialog = NULL;
		if (filename[0] == 0)
			glutLeaveMainLoop();
		else
			load_document();
		if (doc)
		{
			load_page();
			render_page();
			shrinkwrap();
			update_title();
		}
	}
}