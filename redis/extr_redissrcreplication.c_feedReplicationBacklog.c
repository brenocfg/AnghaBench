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
struct TYPE_2__ {scalar_t__ master_repl_offset; size_t repl_backlog_size; size_t repl_backlog_idx; size_t repl_backlog; scalar_t__ repl_backlog_histlen; scalar_t__ repl_backlog_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,unsigned char*,size_t) ; 
 TYPE_1__ server ; 

void feedReplicationBacklog(void *ptr, size_t len) {
    unsigned char *p = ptr;

    server.master_repl_offset += len;

    /* This is a circular buffer, so write as much data we can at every
     * iteration and rewind the "idx" index if we reach the limit. */
    while(len) {
        size_t thislen = server.repl_backlog_size - server.repl_backlog_idx;
        if (thislen > len) thislen = len;
        memcpy(server.repl_backlog+server.repl_backlog_idx,p,thislen);
        server.repl_backlog_idx += thislen;
        if (server.repl_backlog_idx == server.repl_backlog_size)
            server.repl_backlog_idx = 0;
        len -= thislen;
        p += thislen;
        server.repl_backlog_histlen += thislen;
    }
    if (server.repl_backlog_histlen > server.repl_backlog_size)
        server.repl_backlog_histlen = server.repl_backlog_size;
    /* Set the offset of the first byte we have in the backlog. */
    server.repl_backlog_off = server.master_repl_offset -
                              server.repl_backlog_histlen + 1;
}