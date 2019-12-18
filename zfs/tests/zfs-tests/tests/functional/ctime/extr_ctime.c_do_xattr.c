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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int,int) ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int setxattr (char const*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
do_xattr(const char *pfile)
{
	int ret = 0;
	char *value = "user.value";

	if (pfile == NULL) {
		return (-1);
	}

	if (setxattr(pfile, "user.x", value, strlen(value), 0) == -1) {
		(void) fprintf(stderr, "setxattr(%s, %d, %d) failed with errno "
		    "%d\n", pfile, (int)getuid(), (int)getgid(), errno);
		return (1);
	}
	return (ret);
}