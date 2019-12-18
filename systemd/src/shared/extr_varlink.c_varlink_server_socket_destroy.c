#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  address; int /*<<< orphan*/  event_source; TYPE_1__* server; } ;
typedef  TYPE_2__ VarlinkServerSocket ;
struct TYPE_8__ {int /*<<< orphan*/  sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_disable_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockets ; 

__attribute__((used)) static VarlinkServerSocket* varlink_server_socket_destroy(VarlinkServerSocket *ss) {
        if (!ss)
                return NULL;

        if (ss->server)
                LIST_REMOVE(sockets, ss->server->sockets, ss);

        sd_event_source_disable_unref(ss->event_source);

        free(ss->address);
        safe_close(ss->fd);

        return mfree(ss);
}