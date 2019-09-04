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
 int /*<<< orphan*/  printf (char*) ; 

void usage(void)
{
    printf("Usage: mkhive [-?] -h:hive1[,hiveN...] [-u] -d:<dstdir> <inffiles>\n\n"
           "  -h:hiveN  - Comma-separated list of hives to create. Possible values are:\n"
           "              SETUPREG, SYSTEM, SOFTWARE, DEFAULT, SAM, SECURITY, BCD.\n"
           "  -u        - Generate file names in uppercase (default: lowercase) (TEMPORARY FLAG!).\n"
           "  -d:dstdir - The binary hive files are created in this directory.\n"
           "  inffiles  - List of INF files with full path.\n"
           "  -?        - Displays this help screen.\n");
}