#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
struct TYPE_7__ {scalar_t__ used; scalar_t__ buf; int /*<<< orphan*/  free; } ;
typedef  TYPE_2__ aofrwblock ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_8__ {int /*<<< orphan*/  aof_rewrite_buf_blocks; int /*<<< orphan*/  aof_pipe_write_data_to_child; int /*<<< orphan*/  el; scalar_t__ aof_stop_sending_diff; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* listFirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_3__ server ; 
 scalar_t__ write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void aofChildWriteDiffData(aeEventLoop *el, int fd, void *privdata, int mask) {
    listNode *ln;
    aofrwblock *block;
    ssize_t nwritten;
    UNUSED(el);
    UNUSED(fd);
    UNUSED(privdata);
    UNUSED(mask);

    while(1) {
        ln = listFirst(server.aof_rewrite_buf_blocks);
        block = ln ? ln->value : NULL;
        if (server.aof_stop_sending_diff || !block) {
            aeDeleteFileEvent(server.el,server.aof_pipe_write_data_to_child,
                              AE_WRITABLE);
            return;
        }
        if (block->used > 0) {
            nwritten = write(server.aof_pipe_write_data_to_child,
                             block->buf,block->used);
            if (nwritten <= 0) return;
            memmove(block->buf,block->buf+nwritten,block->used-nwritten);
            block->used -= nwritten;
            block->free += nwritten;
        }
        if (block->used == 0) listDelNode(server.aof_rewrite_buf_blocks,ln);
    }
}