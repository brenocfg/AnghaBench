#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pathName ;
struct TYPE_3__ {int /*<<< orphan*/  ourHostName; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_READ_TEXT ; 
 int /*<<< orphan*/  FOPEN_WRITE_TEXT ; 
 int /*<<< orphan*/  FTPInitializeOurHostName (TYPE_1__*) ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessFirewallPrefFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 int /*<<< orphan*/  WriteDefaultFirewallPrefs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _chmod (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 char* gFirewallExceptionList ; 
 char* gFirewallHost ; 
 char* gFirewallPass ; 
 scalar_t__ gFirewallPort ; 
 int gFirewallPrefsLoaded ; 
 int /*<<< orphan*/  gFirewallType ; 
 char* gFirewallUser ; 
 TYPE_1__ gLib ; 
 int gNumProgramRuns ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  kFirewallNotInUse ; 
 int /*<<< orphan*/  kFirewallPrefFileName ; 
 char* kGlobalFirewallPrefFileName ; 
 char* kGlobalFixedFirewallPrefFileName ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

void
LoadFirewallPrefs(int forceReload)
{
	FILE *fp, *fp2;
	char pathName[256];
	char *cp;
	int userFile = 0;
	int sysFile = 0;

	if ((gFirewallPrefsLoaded != 0) && (forceReload == 0))
		return;
	gFirewallPrefsLoaded = 1;

	if (gOurDirectoryPath[0] == '\0')
		return;		/* Don't create in root directory. */
	(void) OurDirectoryPath(pathName, sizeof(pathName), kFirewallPrefFileName);

	/* Set default values. */
	gFirewallType = kFirewallNotInUse;
	gFirewallPort = 0;
	gFirewallHost[0] = '\0';
	gFirewallUser[0] = '\0';
	gFirewallPass[0] = '\0';
	gFirewallExceptionList[0] = '\0';

	fp2 = fopen(kGlobalFirewallPrefFileName, FOPEN_READ_TEXT);
	if (fp2 != NULL) {
		/* Initialize to system-wide defaults. */
		ProcessFirewallPrefFile(fp2);
		(void) fclose(fp2);
		sysFile++;
	}

	fp = fopen(pathName, FOPEN_READ_TEXT);
	if (fp != NULL) {
		/* Do user's firewall file. */
		ProcessFirewallPrefFile(fp);
		(void) fclose(fp);
		userFile = 1;
	}

	fp2 = fopen(kGlobalFixedFirewallPrefFileName, FOPEN_READ_TEXT);
	if (fp2 != NULL) {
		/* Override with system-wide settings. */
		ProcessFirewallPrefFile(fp2);
		(void) fclose(fp2);
		sysFile++;
	}

	if ((userFile == 0) && (sysFile == 0)) {
		/* Create a blank one, if
		 * there were no system-wide files.
		 */
		fp = fopen(pathName, FOPEN_WRITE_TEXT);
		if (fp != NULL) {
			WriteDefaultFirewallPrefs(fp);
			(void) fclose(fp);
			(void) _chmod(pathName, 00600);
			gNumProgramRuns = 1;
		}
	}

	if (gFirewallExceptionList[0] == '\0') {
		FTPInitializeOurHostName(&gLib);
		cp = strchr(gLib.ourHostName, '.');

		if (cp != NULL) {
			(void) STRNCPY(gFirewallExceptionList, cp);
			(void) STRNCAT(gFirewallExceptionList, ",localdomain");
		}
	}
}