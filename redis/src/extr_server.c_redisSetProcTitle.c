#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char** bindaddr; scalar_t__ tls_port; scalar_t__ port; scalar_t__ bindaddr_count; scalar_t__ sentinel_mode; scalar_t__ cluster_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (char*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  setproctitle (char*,char*,char*,scalar_t__,char*) ; 

void redisSetProcTitle(char *title) {
#ifdef USE_SETPROCTITLE
    char *server_mode = "";
    if (server.cluster_enabled) server_mode = " [cluster]";
    else if (server.sentinel_mode) server_mode = " [sentinel]";

    setproctitle("%s %s:%d%s",
        title,
        server.bindaddr_count ? server.bindaddr[0] : "*",
        server.port ? server.port : server.tls_port,
        server_mode);
#else
    UNUSED(title);
#endif
}