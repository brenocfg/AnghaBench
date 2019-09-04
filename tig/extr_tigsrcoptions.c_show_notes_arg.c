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
 char const* opt_notes_arg ; 
 scalar_t__ opt_show_notes ; 

const char *
show_notes_arg()
{
	if (opt_show_notes)
		return opt_notes_arg;
	/* Notes are disabled by default when passing --pretty args. */
	return "";
}