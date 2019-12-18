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
typedef  int /*<<< orphan*/  pathName ;
typedef  int /*<<< orphan*/  path2 ;

/* Variables and functions */
 int /*<<< orphan*/  OurDirectoryPath (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kBookmarkFileName ; 
 int /*<<< orphan*/  kTmpBookmarkFileName ; 
 int /*<<< orphan*/  remove (char*) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int
SwapBookmarkFiles(void)
{
	char pidStr[32];
	char pathName[256], path2[256];

	(void) OurDirectoryPath(path2, sizeof(path2), kBookmarkFileName);
	(void) OurDirectoryPath(pathName, sizeof(pathName), kTmpBookmarkFileName);
	(void) sprintf(pidStr, "-%u.txt", (unsigned int) getpid());
	(void) STRNCAT(pathName, pidStr);

	(void) remove(path2);
	if (rename(pathName, path2) < 0) {
		return (-1);
	}
	return (0);
}