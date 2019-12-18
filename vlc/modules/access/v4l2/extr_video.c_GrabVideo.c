#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct v4l2_buffer {size_t index; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; } ;
struct buffer_t {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EIO 128 
 int /*<<< orphan*/  GetBufferPTS (struct v4l2_buffer*) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VIDIOC_DQBUF ; 
 int /*<<< orphan*/  VIDIOC_QBUF ; 
 TYPE_1__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int) ; 

block_t *GrabVideo (vlc_object_t *demux, int fd,
                    const struct buffer_t *restrict bufv)
{
    struct v4l2_buffer buf = {
        .type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
        .memory = V4L2_MEMORY_MMAP,
    };

    /* Wait for next frame */
    if (v4l2_ioctl (fd, VIDIOC_DQBUF, &buf) < 0)
    {
        switch (errno)
        {
            case EAGAIN:
                return NULL;
            case EIO:
                /* Could ignore EIO, see spec. */
                /* fall through */
            default:
                msg_Err (demux, "dequeue error: %s", vlc_strerror_c(errno));
                return NULL;
        }
    }

    /* Copy frame */
    block_t *block = block_Alloc (buf.bytesused);
    if (unlikely(block == NULL))
        return NULL;
    block->i_pts = block->i_dts = GetBufferPTS (&buf);
    memcpy (block->p_buffer, bufv[buf.index].start, buf.bytesused);

    /* Unlock */
    if (v4l2_ioctl (fd, VIDIOC_QBUF, &buf) < 0)
    {
        msg_Err (demux, "queue error: %s", vlc_strerror_c(errno));
        block_Release (block);
        return NULL;
    }
    return block;
}