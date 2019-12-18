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
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  filebase ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void *
writer(void *a)
{
	int *fd = (int *)a;
	int ret;

	for (;;) {
		if (*fd != -1)
			(void) close (*fd);

		*fd = open(filebase, O_APPEND | O_RDWR | O_CREAT, 0644);
		if (*fd == -1) {
			perror("fail to open test file, refreshing it");
			continue;
		}

		ret = write(*fd, "test\n", 5);
		if (ret != 5)
			perror("writing file");
	}

	return (NULL);
}