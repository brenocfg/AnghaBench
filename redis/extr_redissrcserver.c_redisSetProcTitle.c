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
 int /*<<< orphan*/  UNUSED (char*) ; 

void redisSetProcTitle(char *title) {
#ifdef USE_SETPROCTITLE
    char *server_mode = "";
    if (server.cluster_enabled) server_mode = " [cluster]";
    else if (server.sentinel_mode) server_mode = " [sentinel]";

    setproctitle("%s %s:%d%s",
        title,
        server.bindaddr_count ? server.bindaddr[0] : "*",
        server.port,
        server_mode);
#else
    UNUSED(title);
#endif
}