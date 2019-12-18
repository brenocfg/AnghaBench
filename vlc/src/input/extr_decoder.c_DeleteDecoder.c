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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_9__ {scalar_t__ p_sout_input; } ;
struct decoder_owner {int vout_thread_started; int /*<<< orphan*/  dec; int /*<<< orphan*/  mouse_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_request; int /*<<< orphan*/  wait_acknowledge; int /*<<< orphan*/  wait_fifo; int /*<<< orphan*/ * p_packetizer; scalar_t__ p_description; int /*<<< orphan*/  fmt; int /*<<< orphan*/ * p_vout; int /*<<< orphan*/  i_spu_channel; int /*<<< orphan*/  p_resource; int /*<<< orphan*/ * out_pool; int /*<<< orphan*/  p_aout; TYPE_2__ cc; scalar_t__ p_sout_input; int /*<<< orphan*/  p_fifo; scalar_t__ vctx; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;
struct TYPE_8__ {int i_cat; int /*<<< orphan*/  i_codec; } ;
struct TYPE_10__ {TYPE_1__ fmt_in; } ;
typedef  TYPE_3__ decoder_t ;

/* Variables and functions */
#define  AUDIO_ES 132 
#define  DATA_ES 131 
#define  SPU_ES 130 
#define  UNKNOWN_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  VOUT_SPU_CHANNEL_INVALID ; 
 int /*<<< orphan*/  aout_DecDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (TYPE_3__*) ; 
 int /*<<< orphan*/  decoder_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  decoder_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_Notify (struct decoder_owner*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_PutAout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_resource_PutVout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  on_vout_stopped ; 
 int /*<<< orphan*/  picture_pool_Cancel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_InputDelete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_meta_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_video_context_Release (scalar_t__) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_StopDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_UnregisterSubpictureChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DeleteDecoder( decoder_t * p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    msg_Dbg( p_dec, "killing decoder fourcc `%4.4s'",
             (char*)&p_dec->fmt_in.i_codec );

    const enum es_format_category_e i_cat =p_dec->fmt_in.i_cat;
    if ( p_owner->out_pool )
    {
        picture_pool_Release( p_owner->out_pool );
        p_owner->out_pool = NULL;
    }
    decoder_Clean( p_dec );

    if (p_owner->vctx)
        vlc_video_context_Release( p_owner->vctx );

    /* Free all packets still in the decoder fifo. */
    block_FifoRelease( p_owner->p_fifo );

    /* Cleanup */
#ifdef ENABLE_SOUT
    if( p_owner->p_sout_input )
    {
        sout_InputDelete( p_owner->p_sout_input );
        if( p_owner->cc.p_sout_input )
            sout_InputDelete( p_owner->cc.p_sout_input );
    }
#endif

    switch( i_cat )
    {
        case AUDIO_ES:
            if( p_owner->p_aout )
            {
                /* TODO: REVISIT gap-less audio */
                aout_DecDelete( p_owner->p_aout );
                input_resource_PutAout( p_owner->p_resource, p_owner->p_aout );
            }
            break;
        case VIDEO_ES: {
            vout_thread_t *vout = p_owner->p_vout;

            if (vout != NULL && p_owner->vout_thread_started)
            {
                /* Reset the cancel state that was set before joining the decoder
                 * thread */
                if (p_owner->out_pool)
                    picture_pool_Cancel( p_owner->out_pool, false );
                vout_StopDisplay(vout);
                p_owner->vout_thread_started = false;
                decoder_Notify(p_owner, on_vout_stopped, vout);
                input_resource_PutVout(p_owner->p_resource, vout);
            }
            break;
        }
        case SPU_ES:
        {
            if( p_owner->p_vout )
            {
                assert( p_owner->i_spu_channel != VOUT_SPU_CHANNEL_INVALID );
                decoder_Notify(p_owner, on_vout_stopped, p_owner->p_vout);

                vout_UnregisterSubpictureChannel( p_owner->p_vout,
                                                  p_owner->i_spu_channel );
                vout_Release(p_owner->p_vout);
                p_owner->vout_thread_started = false;
            }
            break;
        }
        case DATA_ES:
        case UNKNOWN_ES:
            break;
        default:
            vlc_assert_unreachable();
    }

    es_format_Clean( &p_owner->fmt );

    if( p_owner->p_description )
        vlc_meta_Delete( p_owner->p_description );

    decoder_Destroy( p_owner->p_packetizer );

    vlc_cond_destroy( &p_owner->wait_fifo );
    vlc_cond_destroy( &p_owner->wait_acknowledge );
    vlc_cond_destroy( &p_owner->wait_request );
    vlc_mutex_destroy( &p_owner->lock );
    vlc_mutex_destroy( &p_owner->mouse_lock );

    decoder_Destroy( &p_owner->dec );
}