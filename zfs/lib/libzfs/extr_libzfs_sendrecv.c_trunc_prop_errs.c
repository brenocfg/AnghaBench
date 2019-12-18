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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
trunc_prop_errs(int truncated)
{
	ASSERT(truncated != 0);

	if (truncated == 1)
		(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
		    "1 more property could not be set\n"));
	else
		(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
		    "%d more properties could not be set\n"), truncated);
}