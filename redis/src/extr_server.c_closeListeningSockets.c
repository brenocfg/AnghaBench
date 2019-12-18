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
struct TYPE_2__ {int ipfd_count; int* ipfd; int tlsfd_count; int* tlsfd; int sofd; int cfd_count; int* cfd; scalar_t__ unixsocket; scalar_t__ cluster_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

void closeListeningSockets(int unlink_unix_socket) {
    int j;

    for (j = 0; j < server.ipfd_count; j++) close(server.ipfd[j]);
    for (j = 0; j < server.tlsfd_count; j++) close(server.tlsfd[j]);
    if (server.sofd != -1) close(server.sofd);
    if (server.cluster_enabled)
        for (j = 0; j < server.cfd_count; j++) close(server.cfd[j]);
    if (unlink_unix_socket && server.unixsocket) {
        serverLog(LL_NOTICE,"Removing the unix socket file.");
        unlink(server.unixsocket); /* don't care if this fails */
    }
}