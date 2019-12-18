#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int paused; size_t stream_offset; size_t buffer_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_space; scalar_t__ buffer; int /*<<< orphan*/  wait_data; int /*<<< orphan*/  interrupt; scalar_t__ error; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t BufferLevel (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_forward_start (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vlc_interrupt_forward_stop (void**) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t Read(stream_t *stream, void *buf, size_t buflen)
{
    stream_sys_t *sys = stream->p_sys;
    size_t copy, offset;
    bool eof;

    if (buflen == 0)
        return buflen;

    vlc_mutex_lock(&sys->lock);
    if (sys->paused)
    {
        msg_Err(stream, "reading while paused (buggy demux?)");
        sys->paused = false;
        vlc_cond_signal(&sys->wait_space);
    }

    while ((copy = BufferLevel(stream, &eof)) == 0 && !eof)
    {
        void *data[2];

        if (sys->error)
        {
            vlc_mutex_unlock(&sys->lock);
            return 0;
        }

        vlc_interrupt_forward_start(sys->interrupt, data);
        vlc_cond_wait(&sys->wait_data, &sys->lock);
        vlc_interrupt_forward_stop(data);
    }

    offset = sys->stream_offset % sys->buffer_size;
    if (copy > buflen)
        copy = buflen;
    /* Do not step past the sharp edge of the circular buffer */
    if (offset + copy > sys->buffer_size)
        copy = sys->buffer_size - offset;

    memcpy(buf, sys->buffer + offset, copy);
    sys->stream_offset += copy;
    vlc_cond_signal(&sys->wait_space);
    vlc_mutex_unlock(&sys->lock);
    return copy;
}