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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pwrite (int,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
rwc_pwrite(int fd, const void *buf, size_t nbytes, off_t offset)
{
	size_t nleft = nbytes;
	ssize_t nwrite = 0;

	nwrite = pwrite(fd, buf, nbytes, offset);
	if (nwrite < 0) {
		perror("pwrite");
		exit(EXIT_FAILURE);
	}

	nleft -= nwrite;
	if (nleft != 0) {
		(void) fprintf(stderr, "warning: pwrite: "
		    "wrote %zu out of %zu bytes\n",
		    (nbytes - nleft), nbytes);
	}
}