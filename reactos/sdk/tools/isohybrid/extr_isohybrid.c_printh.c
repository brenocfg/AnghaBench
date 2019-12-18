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
 char* FMT ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usage () ; 

void
printh(void)
{
#define FMT "%-20s %s\n"

    usage();

    printf("\n");
    printf("Options:\n");
    printf(FMT, "   -h <X>", "Number of geometry heads (default 64)");
    printf(FMT, "   -s <X>", "Number of geometry sectors (default 32)");
    printf(FMT, "   -e --entry", "Specify partition entry number (1-4)");
    printf(FMT, "   -o --offset", "Specify partition offset (default 0)");
    printf(FMT, "   -t --type", "Specify partition type (default 0x17)");
    printf(FMT, "   -i --id", "Specify MBR ID (default random)");
#ifdef REACTOS_ISOHYBRID_EFI_MAC_SUPPORT
    printf(FMT, "   -u --uefi", "Build EFI bootable image");
    printf(FMT, "   -m --mac", "Add AFP table support");
#endif
    printf(FMT, "   -b --mbr <PATH>", "Load MBR from PATH");

    printf("\n");
    printf(FMT, "   --forcehd0", "Assume we are loaded as disk ID 0");
    printf(FMT, "   --ctrlhd0", "Assume disk ID 0 if the Ctrl key is pressed");
    printf(FMT, "   --partok", "Allow booting from within a partition");

    printf("\n");
    printf(FMT, "   -? --help", "Display this help");
    printf(FMT, "   -v --verbose", "Display verbose output");
    printf(FMT, "   -V --version", "Display version information");

    printf("\n");
    printf("Report bugs to <pj.pandit@yahoo.co.in>\n");
}