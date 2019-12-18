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
 int ERANGE ; 
 size_t NDISKS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int* disk_fd ; 
 int errno ; 
 size_t ndisks ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
disk_open(char *path)
{
	int err, fd;

	if (ndisks >= NDISKS)
		return (ERANGE);

	err = 0;
	fd = open(path, O_RDONLY);

	if (fd > 0) {
		disk_fd[ndisks] = fd;
		ndisks++;
	} else 
		err = errno;

	return (err);
}