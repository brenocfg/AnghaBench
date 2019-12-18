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

/* Variables and functions */
 scalar_t__ ui_popup (void const*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_popup_end () ; 
 scalar_t__ ui_popup_item (char const*) ; 

int ui_select(const void *id, const char *current, const char *options[], int n)
{
	int i, choice = -1;
	if (ui_popup(id, current, 0, n))
	{
		for (i = 0; i < n; ++i)
			if (ui_popup_item(options[i]))
				choice = i;
		ui_popup_end();
	}
	return choice;
}