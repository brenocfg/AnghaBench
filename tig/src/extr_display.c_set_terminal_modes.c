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
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaveok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  raw () ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static void
set_terminal_modes(void)
{
	nonl();		/* Disable conversion and detect newlines from input. */
	raw();		/* Take input chars one at a time, no wait for \n */
	noecho();	/* Don't echo input */
	curs_set(0);
	leaveok(stdscr, false);
}