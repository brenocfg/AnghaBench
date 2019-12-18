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
        printf("%s info [OPTIONS] [DEVPATH|FILE]\n\n"
               "Query sysfs or the udev database.\n\n"
               "  -h --help                   Print this message\n"
               "  -V --version                Print version of the program\n"
               "  -q --query=TYPE             Query device information:\n"
               "       name                     Name of device node\n"
               "       symlink                  Pointing to node\n"
               "       path                     sysfs device path\n"
               "       property                 The device properties\n"
               "       all                      All values\n"
               "  -p --path=SYSPATH           sysfs device path used for query or attribute walk\n"
               "  -n --name=NAME              Node or symlink name used for query or attribute walk\n"
               "  -r --root                   Prepend dev directory to path names\n"
               "  -a --attribute-walk         Print all key matches walking along the chain\n"
               "                              of parent devices\n"
               "  -d --device-id-of-file=FILE Print major:minor of device containing this file\n"
               "  -x --export                 Export key/value pairs\n"
               "  -P --export-prefix          Export the key name with a prefix\n"
               "  -e --export-db              Export the content of the udev database\n"
               "  -c --cleanup-db             Clean up the udev database\n"
               "  -w --wait-for-initialization[=SECONDS]\n"
               "                              Wait for device to be initialized\n"
               , program_invocation_short_name);

        return 0;
}