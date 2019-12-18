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
 int /*<<< orphan*/  esclog (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
handle_switch_str(FILE *outFile, char *sw, char *arg, char *desc)
{
    int changed =0;

    if (arg)
    {
        if (strcmp(arg,"") != 0)
        {
            if (strcmp(arg,KDBG_ESC_OFF) == 0)
            {
                if (*sw)
                    changed = 1;
                *sw = '\0';
            }
            else if (strcmp(arg, sw) != 0)
            {
                strcpy(sw, arg);
                changed = 1;
            }
        }
    }
    if (desc)
    {
        esclog(outFile, "%s is \"%s\" (%s)\n", desc, sw, changed ? "changed":"unchanged");
        if (!arg)
            esclog(outFile, "(readonly)\n");
    }

    return changed;
}