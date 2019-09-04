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
typedef  int /*<<< orphan*/  pathName2 ;
typedef  int /*<<< orphan*/  pathName ;

/* Variables and functions */
 int /*<<< orphan*/  OurDirectoryPath (char*,int,char*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/ * gTraceFile ; 
 int /*<<< orphan*/  gTraceTime ; 
 scalar_t__ getpid () ; 
 char* kTraceFileName ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
CloseTrace(void)
{
	char pathName[256];
	char pathName2[256];
	char tName[32];

	if ((gOurDirectoryPath[0] == '\0') || (gTraceFile == NULL))
		return;

	(void) sprintf(tName, "trace.%u", (unsigned int) getpid());
	(void) OurDirectoryPath(pathName, sizeof(pathName), tName);
	(void) OurDirectoryPath(pathName2, sizeof(pathName2), kTraceFileName);

	(void) time(&gTraceTime);
	(void) fprintf(gTraceFile, "SESSION ENDED at:    %s", ctime(&gTraceTime));
	(void) fclose(gTraceFile);

	(void) unlink(pathName2);
	(void) rename(pathName, pathName2);
}