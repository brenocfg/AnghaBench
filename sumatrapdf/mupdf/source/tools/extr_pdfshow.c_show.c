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
 int /*<<< orphan*/  showform () ; 
 int /*<<< orphan*/  showgrep () ; 
 int /*<<< orphan*/  showjs () ; 
 int /*<<< orphan*/  showoutline () ; 
 int /*<<< orphan*/  showpages () ; 
 int /*<<< orphan*/  showpathroot (char*) ; 
 int /*<<< orphan*/  showtrailer () ; 
 int /*<<< orphan*/  showxref () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void show(char *sel)
{
	if (!strcmp(sel, "trailer"))
		showtrailer();
	else if (!strcmp(sel, "xref"))
		showxref();
	else if (!strcmp(sel, "pages"))
		showpages();
	else if (!strcmp(sel, "grep"))
		showgrep();
	else if (!strcmp(sel, "outline"))
		showoutline();
	else if (!strcmp(sel, "js"))
		showjs();
	else if (!strcmp(sel, "form"))
		showform();
	else
		showpathroot(sel);
}