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
 char* KDBG_ESC_OFF ; 
 int /*<<< orphan*/  LINESIZE ; 
 int /*<<< orphan*/  esclog (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
handle_switch_pstr(FILE *outFile, char **psw, char *arg, char *desc)
{
    int changed =0;

    if (arg)
    {
        if (strcmp(arg,"") != 0)
        {
            if (strcmp(arg,KDBG_ESC_OFF) == 0)
            {
                if (*psw)
                    changed = 1;
                free(*psw);
                *psw = NULL;
            }
            else
            {
                if (!*psw)
                {
                    *psw = malloc(LINESIZE);
                    **psw = '\0';
                }

                if (strcmp(arg, *psw) != 0)
                {
                    strcpy(*psw, arg);
                    changed = 1;
                }
            }
        }
    }
    if (desc)
    {
        esclog(outFile, "%s is \"%s\" (%s)\n", desc, *psw, changed ? "changed":"unchanged");
        if (!arg)
            esclog(outFile, "(readonly)\n");
    }

    return changed;
}