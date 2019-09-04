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
struct view {int dummy; } ;

/* Variables and functions */
 size_t current_view ; 
 struct view** display ; 
 int /*<<< orphan*/  doupdate () ; 
 int /*<<< orphan*/  input_mode ; 
 int status_empty ; 
 int /*<<< orphan*/  status_win ; 
 int /*<<< orphan*/  update_view_title (struct view*) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 

void
report_clear(void)
{
	struct view *view = display[current_view];

	if (!view)
		return;

	if (!input_mode && !status_empty) {
		werase(status_win);
		doupdate();
	}
	status_empty = true;
	update_view_title(view);
}