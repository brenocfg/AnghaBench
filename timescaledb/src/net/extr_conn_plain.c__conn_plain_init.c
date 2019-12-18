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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_PLAIN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  plain_ops ; 
 int /*<<< orphan*/  ts_connection_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
_conn_plain_init(void)
{
	/*
	 * WSAStartup is required on Windows before using the Winsock API.
	 * However, PostgreSQL already handles this for us, so it is disabled here
	 * by default. Set WSA_STARTUP_ENABLED to perform this initialization
	 * anyway.
	 */
#if defined(WIN32) && defined(WSA_STARTUP_ENABLED)
	WSADATA wsadata;
	int res;

	res = WSAStartup(MAKEWORD(2, 2), &wsadata);

	if (res != 0)
	{
		elog(ERROR, "WSAStartup failed: %d", res);
		return;
	}
#endif
	ts_connection_register(CONNECTION_PLAIN, &plain_ops);
}