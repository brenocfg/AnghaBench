#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_8__ {int io_threads_num; int /*<<< orphan*/  clients_pending_read; int /*<<< orphan*/  io_threads_do_reads; } ;

/* Variables and functions */
 int CLIENT_PENDING_COMMAND ; 
 int CLIENT_PENDING_READ ; 
 int /*<<< orphan*/  IO_THREADS_OP_READ ; 
 int /*<<< orphan*/  io_threads_active ; 
 int /*<<< orphan*/ * io_threads_list ; 
 int /*<<< orphan*/  io_threads_op ; 
 int* io_threads_pending ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  listEmpty (int /*<<< orphan*/ ) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  processCommandAndResetClient (TYPE_1__*) ; 
 int /*<<< orphan*/  processInputBufferAndReplicate (TYPE_1__*) ; 
 TYPE_2__ server ; 
 scalar_t__ tio_debug ; 

int handleClientsWithPendingReadsUsingThreads(void) {
    if (!io_threads_active || !server.io_threads_do_reads) return 0;
    int processed = listLength(server.clients_pending_read);
    if (processed == 0) return 0;

    if (tio_debug) printf("%d TOTAL READ pending clients\n", processed);

    /* Distribute the clients across N different lists. */
    listIter li;
    listNode *ln;
    listRewind(server.clients_pending_read,&li);
    int item_id = 0;
    while((ln = listNext(&li))) {
        client *c = listNodeValue(ln);
        int target_id = item_id % server.io_threads_num;
        listAddNodeTail(io_threads_list[target_id],c);
        item_id++;
    }

    /* Give the start condition to the waiting threads, by setting the
     * start condition atomic var. */
    io_threads_op = IO_THREADS_OP_READ;
    for (int j = 0; j < server.io_threads_num; j++) {
        int count = listLength(io_threads_list[j]);
        io_threads_pending[j] = count;
    }

    /* Wait for all threads to end their work. */
    while(1) {
        unsigned long pending = 0;
        for (int j = 0; j < server.io_threads_num; j++)
            pending += io_threads_pending[j];
        if (pending == 0) break;
    }
    if (tio_debug) printf("I/O READ All threads finshed\n");

    /* Run the list of clients again to process the new buffers. */
    listRewind(server.clients_pending_read,&li);
    while((ln = listNext(&li))) {
        client *c = listNodeValue(ln);
        c->flags &= ~CLIENT_PENDING_READ;
        if (c->flags & CLIENT_PENDING_COMMAND) {
            c->flags &= ~ CLIENT_PENDING_COMMAND;
            processCommandAndResetClient(c);
        }
        processInputBufferAndReplicate(c);
    }
    listEmpty(server.clients_pending_read);
    return processed;
}