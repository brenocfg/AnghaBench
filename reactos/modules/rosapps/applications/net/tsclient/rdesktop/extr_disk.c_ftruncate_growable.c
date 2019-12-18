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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int ftruncate (int,int) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static int
ftruncate_growable(int fd, off_t length)
{
	int ret;
	off_t pos;
	static const char zero = 0;

	/* Try the simple method first */
	if ((ret = ftruncate(fd, length)) != -1)
	{
		return ret;
	}

	/*
	 * Some kind of error. Perhaps we were trying to grow. Retry
	 * in a safe way.
	 */

	/* Get current position */
	if ((pos = lseek(fd, 0, SEEK_CUR)) == -1)
	{
		perror("lseek");
		return -1;
	}

	/* Seek to new size */
	if (lseek(fd, length, SEEK_SET) == -1)
	{
		perror("lseek");
		return -1;
	}

	/* Write a zero */
	if (write(fd, &zero, 1) == -1)
	{
		perror("write");
		return -1;
	}

	/* Truncate. This shouldn't fail. */
	if (ftruncate(fd, length) == -1)
	{
		perror("ftruncate");
		return -1;
	}

	/* Restore position */
	if (lseek(fd, pos, SEEK_SET) == -1)
	{
		perror("lseek");
		return -1;
	}

	return 0;
}