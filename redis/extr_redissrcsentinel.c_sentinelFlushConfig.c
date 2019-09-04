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
struct TYPE_2__ {int hz; int /*<<< orphan*/  configfile; } ;

/* Variables and functions */
 int CONFIG_DEFAULT_HZ ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fsync (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rewriteConfig (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void sentinelFlushConfig(void) {
    int fd = -1;
    int saved_hz = server.hz;
    int rewrite_status;

    server.hz = CONFIG_DEFAULT_HZ;
    rewrite_status = rewriteConfig(server.configfile);
    server.hz = saved_hz;

    if (rewrite_status == -1) goto werr;
    if ((fd = open(server.configfile,O_RDONLY)) == -1) goto werr;
    if (fsync(fd) == -1) goto werr;
    if (close(fd) == EOF) goto werr;
    return;

werr:
    if (fd != -1) close(fd);
    serverLog(LL_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
}