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
typedef  int mstime_t ;
struct TYPE_2__ {int /*<<< orphan*/ * exec_argv; int /*<<< orphan*/  executable; scalar_t__ maxclients; scalar_t__ configfile; } ;

/* Variables and functions */
 int C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int RESTART_SERVER_CONFIG_REWRITE ; 
 int RESTART_SERVER_GRACEFULLY ; 
 int /*<<< orphan*/  SHUTDOWN_NOFLAGS ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  _exit (int) ; 
 int access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  execve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ prepareForShutdown (int /*<<< orphan*/ ) ; 
 int rewriteConfig (scalar_t__) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zstrdup (int /*<<< orphan*/ ) ; 

int restartServer(int flags, mstime_t delay) {
    int j;

    /* Check if we still have accesses to the executable that started this
     * server instance. */
    if (access(server.executable,X_OK) == -1) {
        serverLog(LL_WARNING,"Can't restart: this process has no "
                             "permissions to execute %s", server.executable);
        return C_ERR;
    }

    /* Config rewriting. */
    if (flags & RESTART_SERVER_CONFIG_REWRITE &&
        server.configfile &&
        rewriteConfig(server.configfile) == -1)
    {
        serverLog(LL_WARNING,"Can't restart: configuration rewrite process "
                             "failed");
        return C_ERR;
    }

    /* Perform a proper shutdown. */
    if (flags & RESTART_SERVER_GRACEFULLY &&
        prepareForShutdown(SHUTDOWN_NOFLAGS) != C_OK)
    {
        serverLog(LL_WARNING,"Can't restart: error preparing for shutdown");
        return C_ERR;
    }

    /* Close all file descriptors, with the exception of stdin, stdout, strerr
     * which are useful if we restart a Redis server which is not daemonized. */
    for (j = 3; j < (int)server.maxclients + 1024; j++) {
        /* Test the descriptor validity before closing it, otherwise
         * Valgrind issues a warning on close(). */
        if (fcntl(j,F_GETFD) != -1) close(j);
    }

    /* Execute the server with the original command line. */
    if (delay) usleep(delay*1000);
    zfree(server.exec_argv[0]);
    server.exec_argv[0] = zstrdup(server.executable);
    execve(server.executable,server.exec_argv,environ);

    /* If an error occurred here, there is nothing we can do, but exit. */
    _exit(1);

    return C_ERR; /* Never reached. */
}