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

__attribute__((used)) static int help(int argc, char *argv[], void *userdata) {

        printf("%s [COMMAND] [OPTIONS...]\n"
               "\n"
               "Mark the boot process as good or bad.\n\n"
               "  -h --help          Show this help\n"
               "     --version       Print version\n"
               "     --path=PATH     Path to the $BOOT partition (may be used multiple times)\n"
               "\n"
               "Commands:\n"
               "     good            Mark this boot as good\n"
               "     bad             Mark this boot as bad\n"
               "     indeterminate   Undo any marking as good or bad\n",
               program_invocation_short_name);

        return 0;
}