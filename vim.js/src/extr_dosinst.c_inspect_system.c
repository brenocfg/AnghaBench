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
struct TYPE_2__ {char* oldexe; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  FALSE ; 
 char NUL ; 
 int TARGET_COUNT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_bat_exe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findoldfile (char**) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (char*) ; 
 char* installdir ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  myexit (int) ; 
 char* oldvimrc ; 
 scalar_t__ pathcmp (char*,int,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int runtimeidx ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 TYPE_1__* targets ; 

__attribute__((used)) static void
inspect_system(void)
{
    char	*p;
    char	buf[BUFSIZE];
    FILE	*fd;
    int		i;
    int		foundone;

    /* This may take a little while, let the user know what we're doing. */
    printf("Inspecting system...\n");

    /*
     * If $VIM is set, check that it's pointing to our directory.
     */
    p = getenv("VIM");
    if (p != NULL && pathcmp(p, -1, installdir, runtimeidx - 1) != 0)
    {
	printf("------------------------------------------------------\n");
	printf("$VIM is set to \"%s\".\n", p);
	printf("This is different from where this version of Vim is:\n");
	strcpy(buf, installdir);
	*(buf + runtimeidx - 1) = NUL;
	printf("\"%s\"\n", buf);
	printf("You must adjust or remove the setting of $VIM,\n");
	if (interactive)
	{
	    printf("to be able to use this install program.\n");
	    myexit(1);
	}
	printf("otherwise Vim WILL NOT WORK properly!\n");
	printf("------------------------------------------------------\n");
    }

    /*
     * If $VIMRUNTIME is set, check that it's pointing to our runtime directory.
     */
    p = getenv("VIMRUNTIME");
    if (p != NULL && pathcmp(p, -1, installdir, -1) != 0)
    {
	printf("------------------------------------------------------\n");
	printf("$VIMRUNTIME is set to \"%s\".\n", p);
	printf("This is different from where this version of Vim is:\n");
	printf("\"%s\"\n", installdir);
	printf("You must adjust or remove the setting of $VIMRUNTIME,\n");
	if (interactive)
	{
	    printf("to be able to use this install program.\n");
	    myexit(1);
	}
	printf("otherwise Vim WILL NOT WORK properly!\n");
	printf("------------------------------------------------------\n");
    }

    /*
     * Check if there is a vim.[exe|bat|, gvim.[exe|bat|, etc. in the path.
     */
    find_bat_exe(FALSE);

    /*
     * A .exe in the install directory may be found anyway on Windows 2000.
     * Check for this situation and find another executable if necessary.
     * w.briscoe@ponl.com 2001-01-20
     */
    foundone = 0;
    for (i = 1; i < TARGET_COUNT; ++i)
    {
	findoldfile(&(targets[i].oldexe));
	if (targets[i].oldexe != NULL)
	    foundone = 1;
    }

    if (foundone)
    {
	printf("Warning: Found Vim executable(s) in your $PATH:\n");
	for (i = 1; i < TARGET_COUNT; ++i)
	    if (targets[i].oldexe != NULL)
		printf("%s\n", targets[i].oldexe);
	printf("It will be used instead of the version you are installing.\n");
	printf("Please delete or rename it, or adjust your $PATH setting.\n");
    }

    /*
     * Check if there is an existing ../_vimrc or ../.vimrc file.
     */
    strcpy(oldvimrc, installdir);
    strcpy(oldvimrc + runtimeidx, "_vimrc");
    if ((fd = fopen(oldvimrc, "r")) == NULL)
    {
	strcpy(oldvimrc + runtimeidx, "vimrc~1"); /* short version of .vimrc */
	if ((fd = fopen(oldvimrc, "r")) == NULL)
	{
	    strcpy(oldvimrc + runtimeidx, ".vimrc");
	    fd = fopen(oldvimrc, "r");
	}
    }
    if (fd != NULL)
	fclose(fd);
    else
	*oldvimrc = NUL;
}