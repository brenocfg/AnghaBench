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
struct timeval {unsigned long tv_sec; unsigned long tv_usec; } ;
struct TYPE_3__ {void* err; int /*<<< orphan*/  sock; } ;
typedef  unsigned long DWORD ;
typedef  TYPE_1__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 void* setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

int
ts_plain_set_timeout(Connection *conn, unsigned long millis)
{
#ifdef WIN32
	/* Timeout is in milliseconds on Windows */
	DWORD timeout = millis;
	int optlen = sizeof(DWORD);
#else
	/* we deliberately use a long constant here instead of a fixed width one because tv_sec is
	 * declared as a long */
	struct timeval timeout = {
		.tv_sec = millis / 1000L,
		.tv_usec = (millis % 1000L) * 1000L,
	};
	int optlen = sizeof(struct timeval);
#endif

	/*
	 * Set send / recv timeout so that write and read don't block forever. Set
	 * separately so that one of the actions failing doesn't block the other.
	 */
	conn->err = setsockopt(conn->sock, SOL_SOCKET, SO_RCVTIMEO, (const char *) &timeout, optlen);

	if (conn->err != 0)
		return -1;

	conn->err = setsockopt(conn->sock, SOL_SOCKET, SO_SNDTIMEO, (const char *) &timeout, optlen);

	if (conn->err != 0)
		return -1;

	return 0;
}