#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* myid; } ;
struct TYPE_3__ {int /*<<< orphan*/ * configfile; } ;

/* Variables and functions */
 int CONFIG_RUN_ID_SIZE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  W_OK ; 
 int access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  getRandomHexChars (scalar_t__*,int) ; 
 TYPE_2__ sentinel ; 
 int /*<<< orphan*/  sentinelFlushConfig () ; 
 int /*<<< orphan*/  sentinelGenerateInitialMonitorEvents () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void sentinelIsRunning(void) {
    int j;

    if (server.configfile == NULL) {
        serverLog(LL_WARNING,
            "Sentinel started without a config file. Exiting...");
        exit(1);
    } else if (access(server.configfile,W_OK) == -1) {
        serverLog(LL_WARNING,
            "Sentinel config file %s is not writable: %s. Exiting...",
            server.configfile,strerror(errno));
        exit(1);
    }

    /* If this Sentinel has yet no ID set in the configuration file, we
     * pick a random one and persist the config on disk. From now on this
     * will be this Sentinel ID across restarts. */
    for (j = 0; j < CONFIG_RUN_ID_SIZE; j++)
        if (sentinel.myid[j] != 0) break;

    if (j == CONFIG_RUN_ID_SIZE) {
        /* Pick ID and persist the config. */
        getRandomHexChars(sentinel.myid,CONFIG_RUN_ID_SIZE);
        sentinelFlushConfig();
    }

    /* Log its ID to make debugging of issues simpler. */
    serverLog(LL_WARNING,"Sentinel ID is %s", sentinel.myid);

    /* We want to generate a +monitor event for every configured master
     * at startup. */
    sentinelGenerateInitialMonitorEvents();
}