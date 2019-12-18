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
 int DATA_RANGE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void
usage(char *prog)
{
	(void) printf("Usage: %s [-v] -o {create,overwrite,append} -f file_name"
	    " [-b block_size]\n"
	    "\t[-s offset] [-c write_count] [-d data]\n\n"
	    "Where [data] equal to zero causes chars "
	    "0->%d to be repeated throughout, or [data]\n"
	    "equal to 'R' for psudorandom data.\n",
	    prog, DATA_RANGE);

	exit(1);
}