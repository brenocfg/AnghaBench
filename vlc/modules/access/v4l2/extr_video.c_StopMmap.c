#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct buffer_t {int /*<<< orphan*/  length; int /*<<< orphan*/  start; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 int /*<<< orphan*/  free (struct buffer_t*) ; 
 int /*<<< orphan*/  v4l2_ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  v4l2_munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void StopMmap (int fd, struct buffer_t *bufv, uint32_t bufc)
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    /* STREAMOFF implicitly dequeues all buffers */
    v4l2_ioctl (fd, VIDIOC_STREAMOFF, &type);
    for (uint32_t i = 0; i < bufc; i++)
        v4l2_munmap (bufv[i].start, bufv[i].length);
    free (bufv);
}