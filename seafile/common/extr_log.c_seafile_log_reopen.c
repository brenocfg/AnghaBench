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
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  logfile ; 
 int /*<<< orphan*/ * logfp ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
seafile_log_reopen ()
{
    FILE *fp, *oldfp;

    if (strcmp(logfile, "-") == 0)
        return 0;

    if ((fp = g_fopen (logfile, "a+")) == NULL) {
        seaf_message ("Failed to open file %s\n", logfile);
        return -1;
    }

    //TODO: check file's health

    oldfp = logfp;
    logfp = fp;
    if (fclose(oldfp) < 0) {
        seaf_message ("Failed to close file %s\n", logfile);
        return -1;
    }

    return 0;
}