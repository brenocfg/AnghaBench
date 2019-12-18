#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ userptr; } ;
struct v4l2_buffer {int /*<<< orphan*/  length; TYPE_1__ m; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int nfds_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_13__ {int fd; int /*<<< orphan*/  es; int /*<<< orphan*/  block_flags; int /*<<< orphan*/  blocksize; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_14__ {void* p_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GetBufferPTS (struct v4l2_buffer*) ; 
 int /*<<< orphan*/  POLLIN ; 
 TYPE_4__* UserPtrQueue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  VIDIOC_DQBUF ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  block_cleanup_push (TYPE_4__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,int,int) ; 
 scalar_t__ v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static void *UserPtrThread (void *data)
{
    demux_t *demux = data;
    demux_sys_t *sys = demux->p_sys;
    int fd = sys->fd;
    struct pollfd ufd[2];
    nfds_t numfds = 1;

    ufd[0].fd = fd;
    ufd[0].events = POLLIN;

    int canc = vlc_savecancel ();
    for (;;)
    {
        struct v4l2_buffer buf = {
            .type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
            .memory = V4L2_MEMORY_USERPTR,
        };
        block_t *block = UserPtrQueue (VLC_OBJECT(demux), fd, sys->blocksize);
        if (block == NULL)
            break;

        /* Wait for data */
        vlc_restorecancel (canc);
        block_cleanup_push (block);
        while (poll (ufd, numfds, -1) == -1)
           if (errno != EINTR)
               msg_Err (demux, "poll error: %s", vlc_strerror_c(errno));
        vlc_cleanup_pop ();
        canc = vlc_savecancel ();

        if (v4l2_ioctl (fd, VIDIOC_DQBUF, &buf) < 0)
        {
            msg_Err (demux, "cannot dequeue buffer: %s",
                     vlc_strerror_c(errno));
            block_Release (block);
            continue;
        }

        assert (block->p_buffer == (void *)buf.m.userptr);
        block->i_buffer = buf.length;
        block->i_pts = block->i_dts = GetBufferPTS (&buf);
        block->i_flags |= sys->block_flags;
        es_out_SetPCR(demux->out, block->i_pts);
        es_out_Send (demux->out, sys->es, block);
    }
    vlc_restorecancel (canc); /* <- hmm, this is purely cosmetic */
    return NULL;
}