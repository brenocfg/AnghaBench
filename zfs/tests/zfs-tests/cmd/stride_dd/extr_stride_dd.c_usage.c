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
 char* execname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void) fprintf(stderr,
	    "usage: %s -i inputfile -o outputfile -b blocksize -c count \n"
	    "           -s stride [ -k seekblocks]\n"
	    "\n"
	    "Simplified version of dd that supports the stride option.\n"
	    "A stride of n means that for each block written, n - 1 blocks\n"
	    "are skipped in both the input and output file. A stride of 1\n"
	    "means that blocks are read and written consecutively.\n"
	    "All numeric parameters must be integers.\n"
	    "\n"
	    "    inputfile:  File to read from\n"
	    "    outputfile: File to write to\n"
	    "    blocksize:  Size of each block to read/write\n"
	    "    count:      Number of blocks to read/write\n"
	    "    stride:     Read/write a block then skip (stride - 1) blocks\n"
	    "    seekblocks: Number of blocks to skip at start of output\n",
	    execname);
	(void) exit(1);
}