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
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* program_invocation_short_name ; 

__attribute__((used)) static void help(void) {
        printf("%s [OPTIONS...] IMAGE\n"
               "%s [OPTIONS...] --mount IMAGE PATH\n"
               "Dissect a file system OS image.\n\n"
               "  -h --help            Show this help\n"
               "     --version         Show package version\n"
               "  -m --mount           Mount the image to the specified directory\n"
               "  -r --read-only       Mount read-only\n"
               "     --discard=MODE    Choose 'discard' mode (disabled, loop, all, crypto)\n"
               "     --root-hash=HASH  Specify root hash for verity\n",
               program_invocation_short_name,
               program_invocation_short_name);
}