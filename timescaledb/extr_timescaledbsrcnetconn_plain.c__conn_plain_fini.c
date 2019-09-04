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

void
_conn_plain_fini(void)
{
#if defined(WIN32) && defined(WSA_STARTUP_ENABLED)
	int ret = WSACleanup();

	if (ret != 0)
		elog(WARNING, "WSACleanup failed");
#endif
}