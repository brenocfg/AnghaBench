#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_20__ {int /*<<< orphan*/  i_reorder_depth; } ;
struct TYPE_21__ {TYPE_6__** pp_decoder; TYPE_3__ desc; } ;
struct decoder_owner {int /*<<< orphan*/  lock; TYPE_4__ cc; int /*<<< orphan*/  p_clock; int /*<<< orphan*/  p_sout; int /*<<< orphan*/  p_resource; } ;
struct TYPE_18__ {int i_channel; int /*<<< orphan*/  i_reorder_depth; } ;
struct TYPE_19__ {TYPE_1__ cc; } ;
struct TYPE_22__ {TYPE_2__ subs; } ;
typedef  TYPE_5__ es_format_t ;
struct TYPE_23__ {int /*<<< orphan*/  p_module; } ;
typedef  TYPE_6__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecoderUnsupportedCodec (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_6__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct decoder_owner* dec_get_owner (TYPE_6__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_DecoderDelete (TYPE_6__*) ; 
 int /*<<< orphan*/  input_DecoderHasCCChanFlag (struct decoder_owner*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* input_DecoderNew (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int input_DecoderSetCcState( decoder_t *p_dec, vlc_fourcc_t codec,
                             int i_channel, bool b_decode )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    //msg_Warn( p_dec, "input_DecoderSetCcState: %d @%x", b_decode, i_channel );

    if( !input_DecoderHasCCChanFlag( p_owner, codec, i_channel ) )
        return VLC_EGENERIC;

    if( b_decode )
    {
        decoder_t *p_cc;
        es_format_t fmt;

        es_format_Init( &fmt, SPU_ES, codec );
        fmt.subs.cc.i_channel = i_channel;
        fmt.subs.cc.i_reorder_depth = p_owner->cc.desc.i_reorder_depth;
        p_cc = input_DecoderNew( VLC_OBJECT(p_dec), &fmt, p_owner->p_clock,
                                 p_owner->p_resource, p_owner->p_sout, false,
                                 NULL, NULL );
        if( !p_cc )
        {
            msg_Err( p_dec, "could not create decoder" );
            vlc_dialog_display_error( p_dec,
                _("Streaming / Transcoding failed"), "%s",
                _("VLC could not open the decoder module.") );
            return VLC_EGENERIC;
        }
        else if( !p_cc->p_module )
        {
            DecoderUnsupportedCodec( p_dec, &fmt, true );
            input_DecoderDelete(p_cc);
            return VLC_EGENERIC;
        }
        struct decoder_owner *p_ccowner = dec_get_owner( p_cc );
        p_ccowner->p_clock = p_owner->p_clock;

        vlc_mutex_lock( &p_owner->lock );
        p_owner->cc.pp_decoder[i_channel] = p_cc;
        vlc_mutex_unlock( &p_owner->lock );
    }
    else
    {
        decoder_t *p_cc;

        vlc_mutex_lock( &p_owner->lock );
        p_cc = p_owner->cc.pp_decoder[i_channel];
        p_owner->cc.pp_decoder[i_channel] = NULL;
        vlc_mutex_unlock( &p_owner->lock );

        if( p_cc )
            input_DecoderDelete(p_cc);
    }
    return VLC_SUCCESS;
}