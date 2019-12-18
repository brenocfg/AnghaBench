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
typedef  int /*<<< orphan*/  mstime_t ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {int hz; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int CLIENTS_CRON_MIN_ITERATIONS ; 
 scalar_t__ clientsCronHandleTimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ clientsCronResizeQueryBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ clientsCronTrackExpansiveClients (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listFirst (int /*<<< orphan*/ ) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRotate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mstime () ; 
 TYPE_1__ server ; 

void clientsCron(void) {
    /* Try to process at least numclients/server.hz of clients
     * per call. Since normally (if there are no big latency events) this
     * function is called server.hz times per second, in the average case we
     * process all the clients in 1 second. */
    int numclients = listLength(server.clients);
    int iterations = numclients/server.hz;
    mstime_t now = mstime();

    /* Process at least a few clients while we are at it, even if we need
     * to process less than CLIENTS_CRON_MIN_ITERATIONS to meet our contract
     * of processing each client once per second. */
    if (iterations < CLIENTS_CRON_MIN_ITERATIONS)
        iterations = (numclients < CLIENTS_CRON_MIN_ITERATIONS) ?
                     numclients : CLIENTS_CRON_MIN_ITERATIONS;

    while(listLength(server.clients) && iterations--) {
        client *c;
        listNode *head;

        /* Rotate the list, take the current head, process.
         * This way if the client must be removed from the list it's the
         * first element and we don't incur into O(N) computation. */
        listRotate(server.clients);
        head = listFirst(server.clients);
        c = listNodeValue(head);
        /* The following functions do different service checks on the client.
         * The protocol is that they return non-zero if the client was
         * terminated. */
        if (clientsCronHandleTimeout(c,now)) continue;
        if (clientsCronResizeQueryBuffer(c)) continue;
        if (clientsCronTrackExpansiveClients(c)) continue;
    }
}