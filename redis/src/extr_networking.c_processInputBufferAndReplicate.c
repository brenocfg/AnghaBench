#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; size_t reploff; int /*<<< orphan*/  pending_querybuf; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {int /*<<< orphan*/  slaves; } ;

/* Variables and functions */
 int CLIENT_MASTER ; 
 int /*<<< orphan*/  processInputBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  replicationFeedSlavesFromMasterStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,size_t,int) ; 
 TYPE_2__ server ; 

void processInputBufferAndReplicate(client *c) {
    if (!(c->flags & CLIENT_MASTER)) {
        processInputBuffer(c);
    } else {
        /* If the client is a master we need to compute the difference
         * between the applied offset before and after processing the buffer,
         * to understand how much of the replication stream was actually
         * applied to the master state: this quantity, and its corresponding
         * part of the replication stream, will be propagated to the
         * sub-replicas and to the replication backlog. */
        size_t prev_offset = c->reploff;
        processInputBuffer(c);
        size_t applied = c->reploff - prev_offset;
        if (applied) {
            replicationFeedSlavesFromMasterStream(server.slaves,
                    c->pending_querybuf, applied);
            sdsrange(c->pending_querybuf,applied,-1);
        }
    }
}