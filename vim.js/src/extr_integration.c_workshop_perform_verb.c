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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char* NOCATGETS (char*) ; 
 int /*<<< orphan*/  dummy ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ save_files ; 
 int /*<<< orphan*/  sd ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*,char*,int,int,int,int,int,int,int,char*) ; 
 scalar_t__ workshop_get_positions (void*,char**,int*,int*,int*,int*,int*,int*,int*,char**) ; 
 int /*<<< orphan*/  workshop_save_files () ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void workshop_perform_verb(char *verb, void *clientData)
{
	char *filename;
	int curLine;
	int curCol;
	int selStartLine;
	int selStartCol;
	int selEndLine;
	int selEndCol;
	int selLength;
	char *selection;

	char buf[2*MAXPATHLEN];
/* Later: needsFilePos indicates whether or not we need to fetch all this
 * info for this verb... for now, however, it looks as if
 * eserve parsing routines depend on it always being present */

	if (workshop_get_positions(clientData,
				   &filename,
				   &curLine,
				   &curCol,
				   &selStartLine,
				   &selStartCol,
				   &selEndLine,
				   &selEndCol,
				   &selLength,
				   &selection)) {
		if (selection == NULL) {
			selection = NOCATGETS("");
		}

		/* Should I save the files??? This is currently done by checking
		   if the verb is one of a few recognized ones. Later we can pass
		   this list from eserve to the editor (it's currently hardcoded in
		   vi and emacs as well). */
		if (save_files) {
			if (!strcmp(verb, "build.build") || !strcmp(verb, "build.build-file") ||
			    !strcmp(verb, "debug.fix") || !strcmp(verb, "debug.fix-all")) {
				workshop_save_files();
			}
		}

		vim_snprintf(buf, sizeof(buf),
			NOCATGETS("toolVerb %s %s %d,%d %d,%d %d,%d %d %s\n"),
			verb,
			filename,
			curLine, curCol,
			selStartLine, selStartCol,
			selEndLine, selEndCol,
			selLength,
			selection);
		dummy = write(sd, buf, strlen(buf));
		if (*selection) {
			free(selection);
		}
	}
}