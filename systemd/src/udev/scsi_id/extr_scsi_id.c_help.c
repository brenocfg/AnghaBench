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

__attribute__((used)) static void help(void) {
        printf("Usage: %s [OPTION...] DEVICE\n\n"
               "SCSI device identification.\n\n"
               "  -h --help                        Print this message\n"
               "     --version                     Print version of the program\n\n"
               "  -d --device=                     Device node for SG_IO commands\n"
               "  -f --config=                     Location of config file\n"
               "  -p --page=0x80|0x83|pre-spc3-83  SCSI page (0x80, 0x83, pre-spc3-83)\n"
               "  -s --sg-version=3|4              Use SGv3 or SGv4\n"
               "  -b --blacklisted                 Treat device as blacklisted\n"
               "  -g --whitelisted                 Treat device as whitelisted\n"
               "  -u --replace-whitespace          Replace all whitespace by underscores\n"
               "  -v --verbose                     Verbose logging\n"
               "  -x --export                      Print values as environment keys\n"
               , program_invocation_short_name);

}