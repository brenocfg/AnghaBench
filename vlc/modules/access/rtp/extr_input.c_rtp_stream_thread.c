#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int ssize_t ;
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_11__ {int fd; int /*<<< orphan*/  session; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_12__ {int i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WAITALL ; 
 TYPE_3__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  block_cleanup_push (TYPE_3__*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_dequeue_force (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_process (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

void *rtp_stream_thread (void *opaque)
{
#ifndef _WIN32
    demux_t *demux = opaque;
    demux_sys_t *sys = demux->p_sys;
    int fd = sys->fd;

    for (;;)
    {
        /* There is no reordering on stream sockets, so no timeout. */
        ssize_t val;

        uint16_t frame_len;
        if (recv (fd, &frame_len, 2, MSG_WAITALL) != 2)
            break;

        block_t *block = block_Alloc (ntohs (frame_len));
        if (unlikely(block == NULL))
            break;

        block_cleanup_push (block);
        val = recv (fd, block->p_buffer, block->i_buffer, MSG_WAITALL);
        vlc_cleanup_pop ();

        if (val != (ssize_t)block->i_buffer)
        {
            block_Release (block);
            break;
        }

        int canc = vlc_savecancel ();
        rtp_process (demux, block);
        rtp_dequeue_force (demux, sys->session);
        vlc_restorecancel (canc);
    }
#else
    (void) opaque;
#endif
    return NULL;
}