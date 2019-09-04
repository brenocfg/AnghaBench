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
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ display_sep ; 
 int /*<<< orphan*/  mvwin (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ newwin (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wresize (scalar_t__,int,int) ; 

__attribute__((used)) static void create_or_move_display_separator(int height, int x)
{
	if (!display_sep) {
		display_sep = newwin(height, 1, 0, x);
		if (!display_sep)
			die("Failed to create separator window");

	} else {
		wresize(display_sep, height, 1);
		mvwin(display_sep, 0, x);
	}
}