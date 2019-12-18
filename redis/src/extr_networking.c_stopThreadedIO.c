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
struct TYPE_2__ {int io_threads_num; int /*<<< orphan*/  clients_pending_write; int /*<<< orphan*/  clients_pending_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handleClientsWithPendingReadsUsingThreads () ; 
 int io_threads_active ; 
 int /*<<< orphan*/ * io_threads_mutex ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ tio_debug ; 

void stopThreadedIO(void) {
    /* We may have still clients with pending reads when this function
     * is called: handle them before stopping the threads. */
    handleClientsWithPendingReadsUsingThreads();
    if (tio_debug) { printf("E"); fflush(stdout); }
    if (tio_debug) printf("--- STOPPING THREADED IO [R%d] [W%d] ---\n",
        (int) listLength(server.clients_pending_read),
        (int) listLength(server.clients_pending_write));
    serverAssert(io_threads_active == 1);
    for (int j = 0; j < server.io_threads_num; j++)
        pthread_mutex_lock(&io_threads_mutex[j]);
    io_threads_active = 0;
}