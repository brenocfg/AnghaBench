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
 int /*<<< orphan*/  udev_builtin_list () ; 

__attribute__((used)) static int help(void) {
        printf("%s test-builtin [OPTIONS] COMMAND DEVPATH\n\n"
               "Test a built-in command.\n\n"
               "  -h --help     Print this message\n"
               "  -V --version  Print version of the program\n\n"
               "Commands:\n"
               , program_invocation_short_name);

        udev_builtin_list();

        return 0;
}