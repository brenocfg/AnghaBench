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
struct TYPE_6__ {int b_has_keyframes; int /*<<< orphan*/  lock; int /*<<< orphan*/  i_buffer_pos; int /*<<< orphan*/  i_last_keyframe_seen_pos; int /*<<< orphan*/  i_buffer_last_pos; } ;
typedef  TYPE_1__ httpd_stream_t ;
struct TYPE_7__ {int i_flags; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_TYPE_I ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  httpd_AppendData (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int httpd_StreamSend(httpd_stream_t *stream, const block_t *p_block)
{
    if (!p_block || !p_block->p_buffer)
        return VLC_SUCCESS;

    vlc_mutex_lock(&stream->lock);

    /* save this pointer (to be used by new connection) */
    stream->i_buffer_last_pos = stream->i_buffer_pos;

    if (p_block->i_flags & BLOCK_FLAG_TYPE_I) {
        stream->b_has_keyframes = true;
        stream->i_last_keyframe_seen_pos = stream->i_buffer_pos;
    }

    httpd_AppendData(stream, p_block->p_buffer, p_block->i_buffer);

    vlc_mutex_unlock(&stream->lock);
    return VLC_SUCCESS;
}