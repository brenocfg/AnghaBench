#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_5__ {size_t len; char* buf; } ;
typedef  TYPE_1__ WSABUF ;
struct TYPE_6__ {int err; int /*<<< orphan*/  sock; } ;
typedef  int DWORD ;
typedef  TYPE_2__ Connection ;

/* Variables and functions */
 scalar_t__ IS_SOCKET_ERROR (int) ; 
 int WSASend (int /*<<< orphan*/ ,TYPE_1__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int send (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
plain_write(Connection *conn, const char *buf, size_t writelen)
{
	ssize_t ret;
#ifdef WIN32
	DWORD b;
	WSABUF wbuf = {
		.len = writelen,
		.buf = (char *) buf,
	};

	conn->err = WSASend(conn->sock, &wbuf, 1, &b, 0, NULL, NULL);

	if (IS_SOCKET_ERROR(conn->err))
		ret = -1;
	else
		ret = b;
#else
	ret = send(conn->sock, buf, writelen, 0);

	if (ret < 0)
		conn->err = ret;
#endif

	return ret;
}