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
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* alloc (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* installdir ; 
 int /*<<< orphan*/  myexit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 scalar_t__ rename (char*,char*) ; 
 char* searchpath_save (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strnicmp (char*,char*,size_t) ; 

__attribute__((used)) static void
findoldfile(char **destination)
{
    char	*bp = *destination;
    size_t	indir_l = strlen(installdir);
    char	*cp = bp + indir_l;
    char	*tmpname;
    char	*farname;

    /*
     * No action needed if exe not found or not in this directory.
     */
    if (bp == NULL
	    || strnicmp(bp, installdir, indir_l) != 0
	    || strchr("/\\", *cp++) == NULL
	    || strchr(cp, '\\') != NULL
	    || strchr(cp, '/') != NULL)
	return;

    tmpname = alloc((int)strlen(cp) + 1);
    strcpy(tmpname, cp);
    tmpname[strlen(tmpname) - 1] = 'x';	/* .exe -> .exx */

    if (access(tmpname, 0) == 0)
    {
	printf("\nERROR: %s and %s clash.  Remove or rename %s.\n",
	    tmpname, cp, tmpname);
	myexit(1);
    }

    if (rename(cp, tmpname) != 0)
    {
	printf("\nERROR: failed to rename %s to %s: %s\n",
	    cp, tmpname, strerror(0));
	myexit(1);
    }

    farname = searchpath_save(cp);

    if (rename(tmpname, cp) != 0)
    {
	printf("\nERROR: failed to rename %s back to %s: %s\n",
	    tmpname, cp, strerror(0));
	myexit(1);
    }

    free(*destination);
    free(tmpname);
    *destination = farname;
}