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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__*,char*) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  opt_buffered ; 
 scalar_t__* opt_logFile ; 
 char* opt_mod ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
set_LogFile(FILE **plogFile)
{
    if (*opt_logFile)
    {
        if (*plogFile)
            fclose(*plogFile);
        *plogFile = NULL;

        if (strcmp(opt_logFile,"none") == 0)
            return 0; //just close

        *plogFile = fopen(opt_logFile, opt_mod ? opt_mod : "a");
        if (*plogFile)
        {
            // disable buffering so fflush is not needed
            if (!opt_buffered)
            {
                l2l_dbg(1, "Disabling log buffering on %s\n", opt_logFile);
                setbuf(*plogFile, NULL);
            }
            else
                l2l_dbg(1, "Enabling log buffering on %s\n", opt_logFile);
        }
        else
        {
            l2l_dbg(0, "Could not open logfile %s (%s)\n", opt_logFile, strerror(errno));
            return 2;
        }
    }
    return 0;
}