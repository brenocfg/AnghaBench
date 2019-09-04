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
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * display_sep ; 

__attribute__((used)) static void remove_display_separator(void)
{
	if (display_sep) {
		delwin(display_sep);
		display_sep = NULL;
	}
}