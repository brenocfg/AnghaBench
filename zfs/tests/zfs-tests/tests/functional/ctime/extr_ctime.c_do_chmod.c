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
 int /*<<< orphan*/  ALL_MODE ; 
 int chmod (char const*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
do_chmod(const char *pfile)
{
	int ret = 0;

	if (pfile == NULL) {
		return (-1);
	}

	if (chmod(pfile, ALL_MODE) == -1) {
		(void) fprintf(stderr, "chmod(%s, ALL_MODE) failed with "
		    "errno %d\n", pfile, errno);
		return (1);
	}

	return (ret);
}