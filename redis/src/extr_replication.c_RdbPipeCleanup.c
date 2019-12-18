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
struct TYPE_2__ {scalar_t__ rdb_pipe_bufflen; int /*<<< orphan*/ * rdb_pipe_buff; scalar_t__ rdb_pipe_numconns_writing; scalar_t__ rdb_pipe_numconns; int /*<<< orphan*/ * rdb_pipe_conns; int /*<<< orphan*/  rdb_pipe_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  checkChildrenDone () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void RdbPipeCleanup() {
    close(server.rdb_pipe_read);
    zfree(server.rdb_pipe_conns);
    server.rdb_pipe_conns = NULL;
    server.rdb_pipe_numconns = 0;
    server.rdb_pipe_numconns_writing = 0;
    zfree(server.rdb_pipe_buff);
    server.rdb_pipe_buff = NULL;
    server.rdb_pipe_bufflen = 0;

    /* Since we're avoiding to detect the child exited as long as the pipe is
     * not drained, so now is the time to check. */
    checkChildrenDone();
}