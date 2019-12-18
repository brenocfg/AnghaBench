#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  p_next; } ;
typedef  TYPE_3__ sout_stream_t ;
struct TYPE_15__ {scalar_t__ downstream_id; TYPE_2__* p_decoder; int /*<<< orphan*/  b_transcode; scalar_t__ b_error; } ;
typedef  TYPE_4__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_12__ {int i_cat; } ;
struct TYPE_13__ {TYPE_1__ fmt_in; } ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int sout_StreamIdSend (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int transcode_audio_process (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int transcode_spu_process (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int transcode_video_process (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *_id, block_t *p_buffer )
{
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    block_t *p_out = NULL;

    if( id->b_error )
        goto error;

    if( !id->b_transcode )
    {
        if( id->downstream_id )
            return sout_StreamIdSend( p_stream->p_next, id->downstream_id, p_buffer );
        else
            goto error;
    }

    int i_ret;
    switch( id->p_decoder->fmt_in.i_cat )
    {
    case AUDIO_ES:
        i_ret = transcode_audio_process( p_stream, id, p_buffer, &p_out );
        break;

    case VIDEO_ES:
        i_ret = transcode_video_process( p_stream, id, p_buffer, &p_out );
        break;

    case SPU_ES:
        i_ret = transcode_spu_process( p_stream, id, p_buffer, &p_out );
        break;

    default:
        goto error;
    }

    if( p_out &&
        sout_StreamIdSend( p_stream->p_next, id->downstream_id, p_out ) )
        i_ret = VLC_EGENERIC;

    return i_ret;
error:
    if( p_buffer )
        block_Release( p_buffer );
    return VLC_EGENERIC;
}