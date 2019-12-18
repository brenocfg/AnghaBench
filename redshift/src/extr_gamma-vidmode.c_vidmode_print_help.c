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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vidmode_print_help(FILE *f)
{
	fputs(_("Adjust gamma ramps with the X VidMode extension.\n"), f);
	fputs("\n", f);

	/* TRANSLATORS: VidMode help output
	   left column must not be translated */
	fputs(_("  screen=N\t\tX screen to apply adjustments to\n"),
	      f);
	fputs("\n", f);
}