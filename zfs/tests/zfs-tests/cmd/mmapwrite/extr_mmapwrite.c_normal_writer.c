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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getpagesize () ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int open (char*,int,int) ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static void *
normal_writer(void *filename)
{
	char *file_path = filename;
	int fd = -1;
	ssize_t write_num = 0;
	int page_size = getpagesize();

	fd = open(file_path, O_RDWR | O_CREAT, 0777);
	if (fd == -1) {
		err(1, "failed to open %s", file_path);
	}

	char *buf = malloc(1);
	while (1) {
		write_num = write(fd, buf, 1);
		if (write_num == 0) {
			err(1, "write failed!");
			break;
		}
		lseek(fd, page_size, SEEK_CUR);
	}

	if (buf) {
		free(buf);
	}
}