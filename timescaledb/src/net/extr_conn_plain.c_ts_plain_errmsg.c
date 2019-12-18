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
struct TYPE_3__ {scalar_t__ err; } ;
typedef  TYPE_1__ Connection ;

/* Variables and functions */
 scalar_t__ IS_SOCKET_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  errno ; 
 char* pgwin32_socket_strerror (int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

const char *
ts_plain_errmsg(Connection *conn)
{
	const char *errmsg = "no connection error";

#ifdef WIN32
	if (IS_SOCKET_ERROR(conn->err))
		errmsg = pgwin32_socket_strerror(WSAGetLastError());
#else
	if (IS_SOCKET_ERROR(conn->err))
		errmsg = strerror(errno);
#endif

	conn->err = 0;

	return errmsg;
}