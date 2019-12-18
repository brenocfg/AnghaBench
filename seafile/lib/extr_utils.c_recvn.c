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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int /*<<< orphan*/ ,char*,size_t) ; 
 int recv (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

ssize_t						/* Read "n" bytes from a descriptor. */
recvn(evutil_socket_t fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
#ifndef WIN32
        if ( (nread = read(fd, ptr, nleft)) < 0)
#else
        if ( (nread = recv(fd, ptr, nleft, 0)) < 0)
#endif
        {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}