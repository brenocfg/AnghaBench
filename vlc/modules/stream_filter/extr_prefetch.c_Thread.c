#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_fast64_t ;
typedef  size_t uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  state; int /*<<< orphan*/  id; } ;
struct stream_ctrl {TYPE_1__ id_state; int /*<<< orphan*/  query; struct stream_ctrl* next; } ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_10__ {int paused; int error; scalar_t__ stream_offset; scalar_t__ buffer_offset; size_t buffer_length; int eof; size_t seek_threshold; size_t buffer_size; int /*<<< orphan*/  wait_data; scalar_t__ buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_space; scalar_t__ can_seek; struct stream_ctrl* controls; int /*<<< orphan*/  interrupt; } ;
typedef  TYPE_3__ stream_sys_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_SET_PAUSE_STATE ; 
 int /*<<< orphan*/  ThreadControl (TYPE_2__*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ ThreadRead (TYPE_2__*,scalar_t__,size_t) ; 
 scalar_t__ ThreadSeek (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct stream_ctrl*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *Thread(void *data)
{
    stream_t *stream = data;
    stream_sys_t *sys = stream->p_sys;
    bool paused = false;

    vlc_interrupt_set(sys->interrupt);

    vlc_mutex_lock(&sys->lock);
    mutex_cleanup_push(&sys->lock);
    for (;;)
    {
        struct stream_ctrl *ctrl = sys->controls;

        if (unlikely(ctrl != NULL))
        {
            sys->controls = ctrl->next;
            ThreadControl(stream, ctrl->query, ctrl->id_state.id,
                          ctrl->id_state.state);
            free(ctrl);
            continue;
        }

        if (sys->paused != paused)
        {   /* Update pause state */
            msg_Dbg(stream, paused ? "resuming" : "pausing");
            paused = sys->paused;
            ThreadControl(stream, STREAM_SET_PAUSE_STATE, paused);
            continue;
        }

        if (paused || sys->error)
        {   /* Wait for not paused and not failed */
            vlc_cond_wait(&sys->wait_space, &sys->lock);
            continue;
        }

        uint_fast64_t stream_offset = sys->stream_offset;

        if (stream_offset < sys->buffer_offset)
        {   /* Need to seek backward */
            if (ThreadSeek(stream, stream_offset) == 0)
            {
                sys->buffer_offset = stream_offset;
                sys->buffer_length = 0;
                assert(!sys->error);
                sys->eof = false;
            }
            else
            {
                sys->error = true;
                vlc_cond_signal(&sys->wait_data);
            }
            continue;
        }

        if (sys->eof)
        {   /* Do not attempt to read at EOF - would busy loop */
            vlc_cond_wait(&sys->wait_space, &sys->lock);
            continue;
        }

        assert(stream_offset >= sys->buffer_offset);

        /* As long as there is space, the buffer will retain already read
         * ("historical") data. The data can be used if/when seeking backward.
         * Unread data is however given precedence if the buffer is full. */
        uint64_t history = stream_offset - sys->buffer_offset;

        /* If upstream supports seeking and if the downstream offset is far
         * beyond the upstream offset, then attempt to skip forward.
         * If it fails, assume upstream is well-behaved such that the failed
         * seek is a no-op, and continue as if seeking was not supported.
         * WARNING: Except problems with misbehaving access plug-ins. */
        if (sys->can_seek
         && history >= (sys->buffer_length + sys->seek_threshold))
        {
            if (ThreadSeek(stream, stream_offset) == 0)
            {
                sys->buffer_offset = stream_offset;
                sys->buffer_length = 0;
                assert(!sys->error);
                assert(!sys->eof);
            }
            else
            {   /* Seek failure is not necessarily fatal here. We could read
                 * data instead until the desired seek offset. But in practice,
                 * not all upstream accesses handle reads after failed seek
                 * correctly. Furthermore, sys->stream_offset and/or
                 * sys->paused might have changed in the mean time. */
                sys->error = true;
                vlc_cond_signal(&sys->wait_data);
            }
            continue;
        }

        assert(sys->buffer_size >= sys->buffer_length);

        size_t len = sys->buffer_size - sys->buffer_length;
        if (len == 0)
        {   /* Buffer is full */
            if (history == 0)
            {   /* Wait for data to be read */
                vlc_cond_wait(&sys->wait_space, &sys->lock);
                continue;
            }

            /* Discard some historical data to make room. */
            len = history > sys->buffer_length ? sys->buffer_length : history;

            sys->buffer_offset += len;
            sys->buffer_length -= len;
        }

        size_t offset = (sys->buffer_offset + sys->buffer_length)
                        % sys->buffer_size;
         /* Do not step past the sharp edge of the circular buffer */
        if (offset + len > sys->buffer_size)
            len = sys->buffer_size - offset;

        ssize_t val = ThreadRead(stream, sys->buffer + offset, len);
        if (val < 0)
            continue;
        if (val == 0)
        {
            assert(len > 0);
            msg_Dbg(stream, "end of stream");
            sys->eof = true;
        }

        assert((size_t)val <= len);
        sys->buffer_length += val;
        assert(sys->buffer_length <= sys->buffer_size);
        //msg_Dbg(stream, "buffer: %zu/%zu", sys->buffer_length,
        //        sys->buffer_size);
        vlc_cond_signal(&sys->wait_data);
    }
    vlc_assert_unreachable();
    vlc_cleanup_pop();
    return NULL;
}