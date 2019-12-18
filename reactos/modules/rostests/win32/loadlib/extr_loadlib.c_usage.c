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
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 

int usage(const char* appName)
{
    dprintf("USAGE: %s libname [libname ...] [unicode]|[ansi] [loop][recurse]\n", appName);
    dprintf("\tWhere libname(s) is one or more libraries to load.\n");
    dprintf("\t[unicode] - perform tests using UNICODE api calls\n");
    dprintf("\t[ansi] - perform tests using ANSI api calls\n");
    dprintf("\t    default is %s\n", TARGET);
    dprintf("\t[loop] - run test process in continuous loop\n");
    dprintf("\t[recurse] - load libraries recursively rather than sequentually\n");
    dprintf("\t[debug] - enable debug mode (unused)\n");
    dprintf("\t[verbose] - enable verbose output (unused)\n");
    return 0;
}