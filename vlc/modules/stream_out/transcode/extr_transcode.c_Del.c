#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  p_next; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_stream_t ;
struct TYPE_19__ {int /*<<< orphan*/  lock; TYPE_4__* id_video; TYPE_4__* id_master_sync; } ;
typedef  TYPE_3__ sout_stream_sys_t ;
struct TYPE_20__ {scalar_t__ downstream_id; TYPE_11__* p_decoder; scalar_t__ b_transcode; } ;
typedef  TYPE_4__ sout_stream_id_sys_t ;
struct TYPE_17__ {int i_cat; } ;
struct TYPE_16__ {TYPE_1__ fmt_in; } ;

/* Variables and functions */
#define  AUDIO_ES 130 
 int /*<<< orphan*/  DeleteSoutStreamID (TYPE_4__*) ; 
#define  SPU_ES 129 
 int /*<<< orphan*/  Send (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int UNKNOWN_ES ; 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  decoder_Destroy (TYPE_11__*) ; 
 int /*<<< orphan*/  sout_StreamIdDel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  transcode_audio_clean (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  transcode_spu_clean (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  transcode_video_clean (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *_id )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;

    if( id->b_transcode )
    {
        int i_cat = id->p_decoder ? id->p_decoder->fmt_in.i_cat : UNKNOWN_ES;
        switch( i_cat )
        {
        case AUDIO_ES:
            Send( p_stream, id, NULL );
            decoder_Destroy( id->p_decoder );
            vlc_mutex_lock( &p_sys->lock );
            if( id == p_sys->id_master_sync )
                p_sys->id_master_sync = NULL;
            vlc_mutex_unlock( &p_sys->lock );
            transcode_audio_clean( p_stream, id );
            break;
        case VIDEO_ES:
            Send( p_stream, id, NULL );
            decoder_Destroy( id->p_decoder );
            vlc_mutex_lock( &p_sys->lock );
            if( id == p_sys->id_video )
                p_sys->id_video = NULL;
            vlc_mutex_unlock( &p_sys->lock );
            transcode_video_clean( p_stream, id );
            break;
        case SPU_ES:
            decoder_Destroy( id->p_decoder );
            transcode_spu_clean( p_stream, id );
            break;
        default:
            break;
        }
    }
    else decoder_Destroy( id->p_decoder );

    if( id->downstream_id ) sout_StreamIdDel( p_stream->p_next, id->downstream_id );

    DeleteSoutStreamID( id );
}