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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 size_t read (int,char*,size_t) ; 

__attribute__((used)) static int
get_random_bytes(char *buf, size_t bytes)
{
	int rand;
	ssize_t bytes_read = 0;

	rand = open("/dev/urandom", O_RDONLY);

	if (rand < 0)
		return (rand);

	while (bytes_read < bytes) {
		ssize_t rc = read(rand, buf + bytes_read, bytes - bytes_read);
		if (rc < 0)
			break;
		bytes_read += rc;
	}

	(void) close(rand);

	return (bytes_read);
}