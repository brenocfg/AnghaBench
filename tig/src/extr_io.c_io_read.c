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
struct io {int eof; scalar_t__ error; int /*<<< orphan*/  pipe; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t
io_read(struct io *io, void *buf, size_t bufsize)
{
	do {
		ssize_t readsize = read(io->pipe, buf, bufsize);

		if (readsize < 0 && (errno == EAGAIN || errno == EINTR))
			continue;
		else if (readsize == -1)
			io->error = errno;
		else if (readsize == 0)
			io->eof = 1;
		return readsize;
	} while (1);
}