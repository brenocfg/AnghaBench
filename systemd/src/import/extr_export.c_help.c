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

        printf("%s [OPTIONS...] {COMMAND} ...\n\n"
               "Export container or virtual machine images.\n\n"
               "  -h --help                    Show this help\n"
               "     --version                 Show package version\n"
               "     --format=FORMAT           Select format\n\n"
               "Commands:\n"
               "  tar NAME [FILE]              Export a TAR image\n"
               "  raw NAME [FILE]              Export a RAW image\n",
               program_invocation_short_name);

        return 0;
}