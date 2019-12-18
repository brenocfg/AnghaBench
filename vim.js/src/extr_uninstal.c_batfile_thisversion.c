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
 int BUFSIZE ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  VIM_VERSION_NODOT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strnicmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
batfile_thisversion(char *path)
{
    FILE	*fd;
    char	line[BUFSIZE];
    char	*p;
    int		ver_len = strlen(VIM_VERSION_NODOT);
    int		found = FALSE;

    fd = fopen(path, "r");
    if (fd != NULL)
    {
	while (fgets(line, BUFSIZE, fd) != NULL)
	{
	    for (p = line; *p != 0; ++p)
		/* don't accept "vim60an" when looking for "vim60". */
		if (strnicmp(p, VIM_VERSION_NODOT, ver_len) == 0
			&& !isdigit(p[ver_len])
			&& !isalpha(p[ver_len]))
		{
		    found = TRUE;
		    break;
		}
	    if (found)
		break;
	}
	fclose(fd);
    }
    return found;
}