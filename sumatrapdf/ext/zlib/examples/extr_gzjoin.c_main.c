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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzcopy (int /*<<< orphan*/ ,int,unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzinit (unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
    unsigned long crc, tot;     /* running crc and total uncompressed length */

    /* skip command name */
    argc--;
    argv++;

    /* show usage if no arguments */
    if (argc == 0) {
        fputs("gzjoin usage: gzjoin f1.gz [f2.gz [f3.gz ...]] > fjoin.gz\n",
              stderr);
        return 0;
    }

    /* join gzip files on command line and write to stdout */
    gzinit(&crc, &tot, stdout);
    while (argc--)
        gzcopy(*argv++, argc, &crc, &tot, stdout);

    /* done */
    return 0;
}