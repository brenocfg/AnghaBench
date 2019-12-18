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
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int ftruncate (int,int) ; 
 int getpagesize () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int munmap (char*,int) ; 
 int open (char*,int,int) ; 

__attribute__((used)) static void *
map_writer(void *filename)
{
	int fd = -1;
	int ret = 0;
	char *buf = NULL;
	int page_size = getpagesize();
	int op_errno = 0;
	char *file_path = filename;

	while (1) {
		ret = access(file_path, F_OK);
		if (ret) {
			op_errno = errno;
			if (op_errno == ENOENT) {
				fd = open(file_path, O_RDWR | O_CREAT, 0777);
				if (fd == -1) {
					err(1, "open file failed");
				}

				ret = ftruncate(fd, page_size);
				if (ret == -1) {
					err(1, "truncate file failed");
				}
			} else {
				err(1, "access file failed!");
			}
		} else {
			fd = open(file_path, O_RDWR, 0777);
			if (fd == -1) {
				err(1, "open file failed");
			}
		}

		if ((buf = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
		    MAP_SHARED, fd, 0)) == MAP_FAILED) {
			err(1, "map file failed");
		}

		if (fd != -1)
			close(fd);

		char s[10] = {0, };
		memcpy(buf, s, 10);
		ret = munmap(buf, page_size);
		if (ret != 0) {
			err(1, "unmap file failed");
		}
	}
}