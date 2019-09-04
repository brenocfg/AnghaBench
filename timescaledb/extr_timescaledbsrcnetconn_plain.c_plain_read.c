#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ err; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Connection ;

/* Variables and functions */
 scalar_t__ recv (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
plain_read(Connection *conn, char *buf, size_t buflen)
{
	ssize_t ret;
#ifdef WIN32
	DWORD b, flags = 0;
	WSABUF wbuf = {
		.len = buflen,
		.buf = buf,
	};

	conn->err = WSARecv(conn->sock, &wbuf, 1, &b, &flags, NULL, NULL);

	if (IS_SOCKET_ERROR(conn->err))
		ret = -1;
	else
		ret = b;
#else
	ret = recv(conn->sock, buf, buflen, 0);

	if (ret < 0)
		conn->err = ret;
#endif

	return ret;
}