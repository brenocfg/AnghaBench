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
struct TYPE_2__ {scalar_t__ master_repl_offset; scalar_t__ repl_backlog_off; scalar_t__ repl_backlog_idx; scalar_t__ repl_backlog_histlen; int /*<<< orphan*/  repl_backlog_size; int /*<<< orphan*/ * repl_backlog; } ;

/* Variables and functions */
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zmalloc (int /*<<< orphan*/ ) ; 

void createReplicationBacklog(void) {
    serverAssert(server.repl_backlog == NULL);
    server.repl_backlog = zmalloc(server.repl_backlog_size);
    server.repl_backlog_histlen = 0;
    server.repl_backlog_idx = 0;

    /* We don't have any data inside our buffer, but virtually the first
     * byte we have is the next byte that will be generated for the
     * replication stream. */
    server.repl_backlog_off = server.master_repl_offset+1;
}