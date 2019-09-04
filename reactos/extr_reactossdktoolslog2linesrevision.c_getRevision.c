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
 int LINESIZE ; 
 int /*<<< orphan*/  PCLOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * POPEN (char*,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,char*) ; 
 char* opt_SourcesPath ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 

int
getRevision(char *fileName, int lastChanged)
{
    char s[LINESIZE];
    FILE *psvn;
    int rev = 0;

    if (!fileName)
        fileName = opt_SourcesPath;
    sprintf(s, "svn info %s", fileName);
    if ((psvn = POPEN(s, "r")))
    {
        while (fgets(s, LINESIZE, psvn))
        {
            if (lastChanged)
            {
                if (sscanf(s, "Last Changed Rev: %d", &rev))
                    break;
            }
            else
            {
                if (sscanf(s, "Revision: %d", &rev))
                    break;
            }
        }
    }
    else
        l2l_dbg(1, "Can't popen: \"%s\"\n", s);

    if (psvn)
        PCLOSE(psvn);

    return rev;
}