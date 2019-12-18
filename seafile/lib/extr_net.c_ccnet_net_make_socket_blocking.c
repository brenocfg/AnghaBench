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
typedef  int /*<<< orphan*/  u_long ;
typedef  int evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  ccnet_warning (char*,int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ccnet_net_make_socket_blocking(evutil_socket_t fd)
{
#ifdef WIN32
	{
		u_long nonblocking = 0;
		if (ioctlsocket(fd, FIONBIO, &nonblocking) == SOCKET_ERROR) {
			ccnet_warning ("fcntl(%d, F_GETFL)", (int)fd);
			return -1;
		}
	}
#else
	{
		int flags;
		if ((flags = fcntl(fd, F_GETFL, NULL)) < 0) {
			ccnet_warning ("fcntl(%d, F_GETFL)", fd);
			return -1;
		}
		if (fcntl(fd, F_SETFL, flags & ~O_NONBLOCK) == -1) {
			ccnet_warning ("fcntl(%d, F_SETFL)", fd);
			return -1;
		}
	}
#endif
	return 0;
}