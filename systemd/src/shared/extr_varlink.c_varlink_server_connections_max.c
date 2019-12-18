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
struct rlimit {int rlim_cur; } ;
struct TYPE_3__ {int connections_max; } ;
typedef  TYPE_1__ VarlinkServer ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int VARLINK_DEFAULT_CONNECTIONS_MAX ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

unsigned varlink_server_connections_max(VarlinkServer *s) {
        struct rlimit rl;

        /* If a server is specified, return the setting for that server, otherwise the default value */
        if (s)
                return s->connections_max;

        assert_se(getrlimit(RLIMIT_NOFILE, &rl) >= 0);

        /* Make sure we never use up more than ¾th of RLIMIT_NOFILE for IPC */
        if (VARLINK_DEFAULT_CONNECTIONS_MAX > rl.rlim_cur / 4 * 3)
                return rl.rlim_cur / 4 * 3;

        return VARLINK_DEFAULT_CONNECTIONS_MAX;
}