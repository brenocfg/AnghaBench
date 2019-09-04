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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ MkDirs (char*,int) ; 
 int /*<<< orphan*/  OurDirectoryPath (char*,size_t,int /*<<< orphan*/ ) ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  kSpoolDir ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int
MkSpoolDir(char *sdir, size_t size)
{
	struct stat st;
	*sdir = '\0';

	/* Don't create in root directory. */
	if (gOurDirectoryPath[0] != '\0') {
		(void) OurDirectoryPath(sdir, size, kSpoolDir);
		if ((stat(sdir, &st) < 0) && (MkDirs(sdir, 00700) < 0)) {
			perror(sdir);
			return (-1);
		} else {
			return (0);
		}
	}
	return (-1);
}