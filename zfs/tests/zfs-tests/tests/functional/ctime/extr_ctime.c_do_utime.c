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
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int utime (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_utime(const char *pfile)
{
	int ret = 0;

	if (pfile == NULL) {
		return (-1);
	}

	/*
	 * Times of the file are set to the current time
	 */
	if (utime(pfile, NULL) == -1) {
		(void) fprintf(stderr, "utime(%s, NULL) failed with errno "
		    "%d\n", pfile, errno);
		return (1);
	}

	return (ret);
}