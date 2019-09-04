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

int
GetSockBufSize(int sockfd, size_t *rsize, size_t *ssize)
{
#ifdef SO_SNDBUF
	int rc = -1;
	int opt;
	int optsize;

	if (ssize != NULL) {
		opt = 0;
		optsize = sizeof(opt);
		rc = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *) &opt, &optsize);
		if (rc == 0)
			*ssize = (size_t) opt;
		else
			*ssize = 0;
	}
	if (rsize != NULL) {
		opt = 0;
		optsize = sizeof(opt);
		rc = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char *) &opt, &optsize);
		if (rc == 0)
			*rsize = (size_t) opt;
		else
			*rsize = 0;
	}
	return (rc);
#else
	if (ssize != NULL)
		*ssize = 0;
	if (rsize != NULL)
		*rsize = 0;
	return (-1);
#endif
}