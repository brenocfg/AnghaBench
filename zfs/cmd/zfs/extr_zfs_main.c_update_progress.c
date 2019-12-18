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
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ pt_begin ; 
 char* pt_header ; 
 int /*<<< orphan*/  pt_reverse ; 
 scalar_t__ pt_shown ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_progress(char *update)
{
	if (!pt_shown && time(NULL) > pt_begin) {
		int len = strlen(update);

		(void) printf("%s: %s%*.*s", pt_header, update, len, len,
		    pt_reverse);
		(void) fflush(stdout);
		pt_shown = B_TRUE;
	} else if (pt_shown) {
		int len = strlen(update);

		(void) printf("%s%*.*s", update, len, len, pt_reverse);
		(void) fflush(stdout);
	}
}