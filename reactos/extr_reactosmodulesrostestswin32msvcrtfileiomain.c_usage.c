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
 int /*<<< orphan*/  printf (char*,...) ; 

int usage(char* argv0)
{
    printf("USAGE: %s test_id [unicode]|[ansi] [clean]|[status][verbose]\n", argv0);
    printf("\tWhere test_id is one of:\n");
    printf("\t0 - (default) regression mode, run tests 1-4 displaying failures only\n");
    printf("\t1 - Write DOS style eol data to file in text mode (text.dos)\n");
    printf("\t2 - Write NIX style eol data to file in binary mode (binary.dos)\n");
    printf("\t3 - Write DOS style eol data to file in text mode (text.nix)\n");
    printf("\t4 - Write NIX style eol data to file in binary mode (binary.nix)\n");
    printf("\t5 - Echo console line input\n");
    printf("\t6 - Dump console line input in hex format\n");
    printf("\t7 - The source code is your friend\n");
    printf("\t[unicode] - perform tests using UNICODE versions of library functions\n");
    printf("\t[ansi] - perform tests using ANSI versions of library functions\n");
    printf("\t    If neither unicode or ansi is specified build default is used\n");
    printf("\t[clean] - delete all temporary test output files\n");
    printf("\t[status] - enable extra status display while running\n");
    printf("\t[verbose] - enable verbose output when running\n");
    return 0;
}