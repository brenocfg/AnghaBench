#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_20__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_30__ {int /*<<< orphan*/  lock; } ;
struct TYPE_27__ {int /*<<< orphan*/  i_rate; } ;
struct TYPE_28__ {TYPE_11__ audio; } ;
struct TYPE_31__ {int b_error; scalar_t__ (* pf_drift_validate ) (int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ i_drift; int /*<<< orphan*/  encoder; int /*<<< orphan*/ * p_af_chain; int /*<<< orphan*/  next_input_pts; TYPE_2__ fifo; int /*<<< orphan*/  callback_data; TYPE_5__* p_enccfg; scalar_t__ downstream_id; TYPE_20__* p_decoder; scalar_t__ (* pf_transcode_downstream_add ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_1__ decoder_out; int /*<<< orphan*/  p_filterscfg; TYPE_11__ fmt_input_audio; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;
struct TYPE_32__ {scalar_t__ i_pts; scalar_t__ i_dts; int /*<<< orphan*/  i_nb_samples; struct TYPE_32__* p_next; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_34__ {int /*<<< orphan*/  audio; } ;
struct TYPE_33__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_29__ {int (* pf_decode ) (TYPE_20__*,TYPE_4__*) ;int /*<<< orphan*/  fmt_in; } ;

/* Variables and functions */
 int VLCDEC_SUCCESS ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  aout_FiltersDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* aout_FiltersPlay (int /*<<< orphan*/ *,TYPE_4__*,float) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_4__**,TYPE_4__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*) ; 
 int stub1 (TYPE_20__*,TYPE_4__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ transcode_audio_filters_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  transcode_audio_format_IsSimilar (TYPE_11__*,TYPE_11__*) ; 
 TYPE_4__* transcode_dequeue_all_audios (TYPE_3__*) ; 
 int /*<<< orphan*/  transcode_encoder_audio_configure (TYPE_5__*,TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  transcode_encoder_drain (int /*<<< orphan*/ ,TYPE_4__**) ; 
 TYPE_4__* transcode_encoder_encode (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_6__* transcode_encoder_format_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_encoder_format_out (int /*<<< orphan*/ ) ; 
 scalar_t__ transcode_encoder_open (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ transcode_encoder_opened (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int transcode_audio_process( sout_stream_t *p_stream,
                                    sout_stream_id_sys_t *id,
                                    block_t *in, block_t **out )
{
    *out = NULL;

    int ret = id->p_decoder->pf_decode( id->p_decoder, in );
    if( ret != VLCDEC_SUCCESS )
        return VLC_EGENERIC;

    block_t *p_audio_bufs = transcode_dequeue_all_audios( id );

    do
    {
        block_t *p_audio_buf = p_audio_bufs;
        if( p_audio_buf == NULL )
            break;
        p_audio_bufs = p_audio_buf->p_next;
        p_audio_buf->p_next = NULL;

        if( id->b_error )
        {
            block_Release( p_audio_buf );
            continue;
        }

        vlc_mutex_lock(&id->fifo.lock);

        if( p_audio_buf && ( unlikely(!transcode_encoder_opened( id->encoder )) ||
            !transcode_audio_format_IsSimilar( &id->fmt_input_audio, &id->decoder_out.audio ) ) )
        {
            if( !transcode_encoder_opened( id->encoder ) )
            {
                transcode_encoder_audio_configure( id->p_enccfg,
                                                   &id->decoder_out.audio, id->encoder, true );
                id->fmt_input_audio = id->decoder_out.audio;
            }
            else
            {
                /* Check if audio format has changed, and filters need reinit */
                msg_Info( p_stream, "Audio changed, trying to reinitialize filters" );
                if( id->p_af_chain != NULL )
                {
                    aout_FiltersDelete( p_stream, id->p_af_chain );
                    id->p_af_chain = NULL;
                }
                id->fmt_input_audio = id->decoder_out.audio;
            }

            if( !id->p_af_chain &&
                transcode_audio_filters_init( p_stream,
                                              id->p_filterscfg,
                                              &id->decoder_out.audio,
                                              &transcode_encoder_format_in( id->encoder )->audio,
                                              &id->p_af_chain ) )
            {
                vlc_mutex_unlock(&id->fifo.lock);
                goto error;
            }

            date_Init( &id->next_input_pts, id->decoder_out.audio.i_rate, 1 );
            date_Set( &id->next_input_pts, p_audio_buf->i_pts );

            if( !transcode_encoder_opened( id->encoder ) &&
                transcode_encoder_open( id->encoder, id->p_enccfg ) )
            {
                vlc_mutex_unlock(&id->fifo.lock);
                goto error;
            }

            if( !id->downstream_id )
                id->downstream_id =
                    id->pf_transcode_downstream_add( p_stream,
                                                     &id->p_decoder->fmt_in,
                                                     transcode_encoder_format_out( id->encoder ) );
            if( !id->downstream_id )
            {
                msg_Err( p_stream, "cannot output transcoded stream %4.4s",
                                   (char *) &id->p_enccfg->i_codec );
                vlc_mutex_unlock(&id->fifo.lock);
                goto error;
            }
        }

        vlc_mutex_unlock(&id->fifo.lock);

        if( id->pf_drift_validate )
        {
            vlc_tick_t i_pts = date_Get( &id->next_input_pts );
            vlc_tick_t i_drift = 0;

            if( likely( p_audio_buf->i_pts != VLC_TICK_INVALID ) )
                i_drift = p_audio_buf->i_pts - i_pts;
            if( id->pf_drift_validate( id->callback_data, i_drift ) != VLC_SUCCESS )
            {
                date_Set( &id->next_input_pts, p_audio_buf->i_pts );
                i_drift = 0;
            }

            vlc_mutex_lock(&id->fifo.lock);
            id->i_drift = i_drift;
            vlc_mutex_unlock(&id->fifo.lock);
            date_Increment( &id->next_input_pts, p_audio_buf->i_nb_samples );
        }

        p_audio_buf->i_dts = p_audio_buf->i_pts;

        /* Run filter chain */
        p_audio_buf = aout_FiltersPlay( id->p_af_chain, p_audio_buf, 1.f );
        if( p_audio_buf  )
        {
            p_audio_buf->i_dts = p_audio_buf->i_pts;

            block_t *p_block = transcode_encoder_encode( id->encoder, p_audio_buf );
            block_ChainAppend( out, p_block );
            block_Release( p_audio_buf );
        }
        continue;
error:
        if( p_audio_buf )
            block_Release( p_audio_buf );
        id->b_error = true;
    } while( p_audio_bufs );

    /* Drain encoder */
    if( unlikely( !id->b_error && in == NULL ) && transcode_encoder_opened( id->encoder ) )
    {
        transcode_encoder_drain( id->encoder, out );
    }

    return id->b_error ? VLC_EGENERIC : VLC_SUCCESS;
}