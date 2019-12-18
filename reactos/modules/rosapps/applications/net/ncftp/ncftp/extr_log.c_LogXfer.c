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
 int /*<<< orphan*/  FOPEN_APPEND_TEXT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const* const,char const* const) ; 
 int /*<<< orphan*/  gLogFileName ; 
 scalar_t__ gMaxLogSize ; 

void
LogXfer(const char *const mode, const char *const url)
{
	FILE *fp;

	if (gMaxLogSize == 0)
		return;		/* Don't log */

	fp = fopen(gLogFileName, FOPEN_APPEND_TEXT);
	if (fp != NULL) {
		(void) fprintf(fp, "  %s %s\n", mode, url);
		(void) fclose(fp);
	}
}