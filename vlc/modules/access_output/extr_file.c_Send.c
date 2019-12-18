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
typedef  scalar_t__ ssize_t ;
struct TYPE_8__ {int* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_9__ {size_t i_buffer; int /*<<< orphan*/  p_buffer; struct TYPE_9__* p_next; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static ssize_t Send(sout_access_out_t *access, block_t *block)
{
    int *fdp = access->p_sys, fd = *fdp;
    size_t total = 0;

    while (block != NULL)
    {
        if (block->i_buffer == 0)
        {
            block_t *next = block->p_next;
            block_Release(block);
            block = next;
            continue;
        }

        /* TODO: vectorized I/O with sendmsg() */
        ssize_t val = send(fd, block->p_buffer, block->i_buffer, MSG_NOSIGNAL);
        if (val <= 0)
        {   /* FIXME: errno is meaningless if val is zero */
            if (errno == EINTR)
                continue;
            block_ChainRelease(block);
            msg_Err(access, "cannot write: %s", vlc_strerror_c(errno));
            return -1;
        }

        total += val;

        assert((size_t)val <= block->i_buffer);
        block->p_buffer += val;
        block->i_buffer -= val;
    }
    return total;
}