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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char NUL ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 char* getenv (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  setDollarVim (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  vim_FullName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void
findYourself(
    char	*argv0)
{
    char	*runpath = NULL;
    char	*path;
    char	*pathbuf;

    if (*argv0 == '/')
	runpath = strdup(argv0);
    else if (*argv0 == '.' || strchr(argv0, '/'))
    {
	runpath = (char *) malloc(MAXPATHLEN);
	if (getcwd(runpath, MAXPATHLEN) == NULL)
	    runpath[0] = NUL;
	strcat(runpath, "/");
	strcat(runpath, argv0);
    }
    else
    {
	path = getenv("PATH");
	if (path != NULL)
	{
	    runpath = (char *) malloc(MAXPATHLEN);
	    pathbuf = strdup(path);
	    path = strtok(pathbuf, ":");
	    do
	    {
		strcpy(runpath, path);
		strcat(runpath, "/");
		strcat(runpath, argv0);
		if (access(runpath, X_OK) == 0)
		    break;
	    } while ((path = strtok(NULL, ":")) != NULL);
	    free(pathbuf);
	}
    }

    if (runpath != NULL)
    {
	char runbuf[MAXPATHLEN];

	/*
	 * We found the run directory. Now find the install dir.
	 */
	(void)vim_FullName((char_u *)runpath, (char_u *)runbuf, MAXPATHLEN, 1);
	path = strrchr(runbuf, '/');
	if (path != NULL)
	    *path = NUL;		/* remove the vim/gvim name */
	path = strrchr(runbuf, '/');
	if (path != NULL)
	{
	    if (strncmp(path, "/bin", 4) == 0)
		setDollarVim(runbuf);
	    else if (strncmp(path, "/src", 4) == 0)
	    {
		*path = NUL;	/* development tree */
		setDollarVim(runbuf);
	    }
	}
	free(runpath);
    }
}