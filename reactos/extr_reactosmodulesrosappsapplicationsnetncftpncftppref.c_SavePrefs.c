#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pathName2 ;
typedef  int /*<<< orphan*/  pathName ;
struct TYPE_2__ {scalar_t__ visible; char* varname; int /*<<< orphan*/  (* proc ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_WRITE_TEXT ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int gNumPrefOpts ; 
 TYPE_1__* gPrefOpts ; 
 scalar_t__ gPrefsDirty ; 
 scalar_t__ getpid () ; 
 char* kPrefFileName ; 
 scalar_t__ kPrefOptObselete ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
SavePrefs(void)
{
	char pathName[256];
	char pathName2[256];
	char tName[32];
	int t;
	FILE *fp;

	if (gPrefsDirty == 0)
		return;		/* Don't need to save -- no changes made. */

	(void) OurDirectoryPath(pathName, sizeof(pathName), kPrefFileName);

	(void) sprintf(tName, "tpref%06u.txt", (unsigned int) getpid());
	(void) OurDirectoryPath(pathName2, sizeof(pathName2), tName);

	fp = fopen(pathName2, FOPEN_WRITE_TEXT);
	if (fp == NULL) {
		perror("could not save preferences file");
	} else {
		(void) fprintf(fp, "%s", "# NcFTP 3 preferences file\n# This file is loaded and overwritten each time NcFTP is run.\n#\n");
		for (t=0; t<gNumPrefOpts; t++) {
			if (gPrefOpts[t].visible != kPrefOptObselete) {
				(void) fprintf(fp, "%s=", gPrefOpts[t].varname);
				(*gPrefOpts[t].proc)(t, NULL, fp);
				(void) fprintf(fp, "\n");
			}
		}
		(void) fclose(fp);
		(void) unlink(pathName);
		if (rename(pathName2, pathName) < 0) {
			perror("could not finish saving preferences file");
			(void) unlink(pathName2);
		};
	}
}