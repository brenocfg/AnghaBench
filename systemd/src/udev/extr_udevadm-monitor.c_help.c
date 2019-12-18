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
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* program_invocation_short_name ; 

__attribute__((used)) static int help(void) {
        printf("%s monitor [OPTIONS]\n\n"
               "Listen to kernel and udev events.\n\n"
               "  -h --help                                Show this help\n"
               "  -V --version                             Show package version\n"
               "  -p --property                            Print the event properties\n"
               "  -k --kernel                              Print kernel uevents\n"
               "  -u --udev                                Print udev events\n"
               "  -s --subsystem-match=SUBSYSTEM[/DEVTYPE] Filter events by subsystem\n"
               "  -t --tag-match=TAG                       Filter events by tag\n"
               , program_invocation_short_name);

        return 0;
}