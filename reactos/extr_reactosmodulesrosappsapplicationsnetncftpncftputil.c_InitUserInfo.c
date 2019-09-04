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
struct passwd {char* pw_dir; char* pw_name; char* pw_shell; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitOurDirectory () ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gHome ; 
 int /*<<< orphan*/  gShell ; 
 scalar_t__ gUid ; 
 int /*<<< orphan*/  gUser ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 struct passwd* getpwuid (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

void
InitUserInfo(void)
{
#if defined(WIN32) || defined(_WINDOWS)
	DWORD nSize;
	char *cp;

	memset(gUser, 0, sizeof(gUser));
	nSize = sizeof(gUser) - 1;
	if (! GetUserName(gUser, &nSize))
		STRNCPY(gUser, "default");

	memset(gHome, 0, sizeof(gHome));
	(void) GetTempPath((DWORD) sizeof(gHome) - 1, gHome);
	cp = strrchr(gHome, '\\');
	if ((cp != NULL) && (cp[1] == '\0'))
		*cp = '\0';

	memset(gShell, 0, sizeof(gShell));
#else
	struct passwd *pwptr;
	char *envp;

	gUid = geteuid();
	pwptr = getpwuid(gUid);

	if (pwptr == NULL) {
		envp = getenv("LOGNAME");
		if (envp == NULL) {
			(void) fprintf(stderr, "Who are you?\n");
			(void) fprintf(stderr, "You have a user id number of %d, but no username associated with it.\n", (int) gUid);
			(void) STRNCPY(gUser, "unknown");
		} else {
			(void) STRNCPY(gUser, envp);
		}

		envp = getenv("HOME");
		if (envp == NULL)
			(void) STRNCPY(gHome, "/");
		else
			(void) STRNCPY(gHome, envp);

		envp = getenv("SHELL");
		if (envp == NULL)
			(void) STRNCPY(gShell, "/bin/sh");
		else
			(void) STRNCPY(gShell, envp);
	} else {
		/* Copy home directory. */
		(void) STRNCPY(gHome, pwptr->pw_dir);

		/* Copy user name. */
		(void) STRNCPY(gUser, pwptr->pw_name);

		/* Copy shell. */
		(void) STRNCPY(gShell, pwptr->pw_shell);
	}
#endif

	InitOurDirectory();
}