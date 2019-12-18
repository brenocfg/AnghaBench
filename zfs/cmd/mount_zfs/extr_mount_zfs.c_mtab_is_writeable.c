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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int lstat (char*,struct stat*) ; 
 int open (char*,int,int) ; 

__attribute__((used)) static int
mtab_is_writeable(void)
{
	struct stat st;
	int error, fd;

	error = lstat("/etc/mtab", &st);
	if (error || S_ISLNK(st.st_mode))
		return (0);

	fd = open("/etc/mtab", O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (0);

	close(fd);
	return (1);
}