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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  pathName ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FOPEN_READ_TEXT ; 
 int /*<<< orphan*/  FOPEN_WRITE_TEXT ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int gNumProgramRuns ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  gPrefsDirty ; 
 int /*<<< orphan*/  kFirstFileName ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
CheckForNewV3User(void)
{
	FILE *fp;
	struct stat st;
	char pathName[256];
	char line[256];

	gNumProgramRuns = 0;

	/* Don't create in root directory. */
	if (gOurDirectoryPath[0] != '\0') {
		(void) OurDirectoryPath(pathName, sizeof(pathName), kFirstFileName);

		if ((stat(pathName, &st) < 0) && (errno == ENOENT)) {
			gNumProgramRuns = 1;
			gPrefsDirty++;

			/* Create a blank one. */
			fp = fopen(pathName, FOPEN_WRITE_TEXT);
			if (fp == NULL)
				return;
			(void) fprintf(fp, "# NcFTP uses this file to mark that you have run it before, and that you do not\n# need any special first-time instructions or setup.\n#\nruns=%d\n", gNumProgramRuns);
			(void) fclose(fp);
		} else {
			fp = fopen(pathName, FOPEN_READ_TEXT);
			if (fp != NULL) {
				while (fgets(line, sizeof(line) - 1, fp) != NULL) {
					if (strncmp(line, "runs=", 5) == 0) {
						(void) sscanf(line + 5, "%d",
							&gNumProgramRuns);
						break;
					}
				}
				(void) fclose(fp);
			}

			/* Increment the count of program runs. */
			gNumProgramRuns++;
			if (gNumProgramRuns == 1)
				gPrefsDirty++;

			/* Race condition between other ncftp processes.
			 * This isn't a big deal because this counter isn't
			 * critical.
			 */

			fp = fopen(pathName, FOPEN_WRITE_TEXT);
			if (fp != NULL) {
				(void) fprintf(fp, "# NcFTP uses this file to mark that you have run it before, and that you do not\n# need any special first-time instructions or setup.\n#\nruns=%d\n", gNumProgramRuns);
				(void) fclose(fp);
			}
		}
	}
}