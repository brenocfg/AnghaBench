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
struct TYPE_2__ {long long repl_backlog_size; scalar_t__ master_repl_offset; scalar_t__ repl_backlog_off; scalar_t__ repl_backlog_idx; scalar_t__ repl_backlog_histlen; int /*<<< orphan*/ * repl_backlog; } ;

/* Variables and functions */
 long long CONFIG_REPL_BACKLOG_MIN_SIZE ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zmalloc (long long) ; 

void resizeReplicationBacklog(long long newsize) {
    if (newsize < CONFIG_REPL_BACKLOG_MIN_SIZE)
        newsize = CONFIG_REPL_BACKLOG_MIN_SIZE;
    if (server.repl_backlog_size == newsize) return;

    server.repl_backlog_size = newsize;
    if (server.repl_backlog != NULL) {
        /* What we actually do is to flush the old buffer and realloc a new
         * empty one. It will refill with new data incrementally.
         * The reason is that copying a few gigabytes adds latency and even
         * worse often we need to alloc additional space before freeing the
         * old buffer. */
        zfree(server.repl_backlog);
        server.repl_backlog = zmalloc(server.repl_backlog_size);
        server.repl_backlog_histlen = 0;
        server.repl_backlog_idx = 0;
        /* Next byte we have is... the next since the buffer is empty. */
        server.repl_backlog_off = server.master_repl_offset+1;
    }
}