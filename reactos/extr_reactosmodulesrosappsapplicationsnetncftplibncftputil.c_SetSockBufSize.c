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
SetSockBufSize(int sockfd, size_t rsize, size_t ssize)
{
#ifdef SO_SNDBUF
	int rc = -1;
	int opt;
	int optsize;

#ifdef TCP_RFC1323
	/* This is an AIX-specific socket option to do RFC1323 large windows */
	if (ssize > 0 || rsize > 0) {
		opt = 1;
		optsize = sizeof(opt);
		rc = setsockopt(sockfd, IPPROTO_TCP, TCP_RFC1323, &opt, optsize);
	}
#endif

	if (ssize > 0) {
		opt = (int) ssize;
		optsize = sizeof(opt);
		rc = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *) &opt, optsize);
	}
	if (rsize > 0) {
		opt = (int) rsize;
		optsize = sizeof(opt);
		rc = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char *) &opt, optsize);
	}
	return (rc);
#else
	return (-1);
#endif
}