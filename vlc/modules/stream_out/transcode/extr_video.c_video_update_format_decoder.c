#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct decoder_owner {int /*<<< orphan*/ * p_obj; TYPE_2__* id; } ;
struct TYPE_17__ {int /*<<< orphan*/  lock; } ;
struct TYPE_16__ {int /*<<< orphan*/  video; } ;
struct TYPE_18__ {TYPE_1__ fifo; TYPE_11__ decoder_out; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  filter_chain_t ;
struct TYPE_19__ {scalar_t__ i_codec; } ;
typedef  TYPE_3__ es_format_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_22__ {scalar_t__ i_codec; TYPE_6__ video; } ;
struct TYPE_20__ {TYPE_8__ fmt_out; int /*<<< orphan*/  fmt_in; } ;
typedef  TYPE_4__ decoder_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (TYPE_4__*) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_11__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_11__*,TYPE_8__*) ; 
 int /*<<< orphan*/  es_format_SetMeta (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int filter_chain_AppendConverter (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  filter_chain_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_chain_NewVideo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_chain_Reset (int /*<<< orphan*/ *,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,char*) ; 
 TYPE_3__* transcode_encoder_format_in (int /*<<< orphan*/ ) ; 
 scalar_t__ video_format_IsSimilar (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int video_update_format_decoder( decoder_t *p_dec, vlc_video_context *vctx )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    sout_stream_id_sys_t *id = p_owner->id;
    vlc_object_t        *p_obj = p_owner->p_obj;
    filter_chain_t       *test_chain;

    vlc_mutex_lock( &id->fifo.lock );

    const es_format_t *p_enc_in = transcode_encoder_format_in( id->encoder );

    if( p_enc_in->i_codec == p_dec->fmt_out.i_codec ||
        video_format_IsSimilar( &id->decoder_out.video, &p_dec->fmt_out.video ) )
    {
        vlc_mutex_unlock( &id->fifo.lock );
        return 0;
    }

    es_format_Clean( &id->decoder_out );
    es_format_Copy( &id->decoder_out, &p_dec->fmt_out );

    /* crap, decoders resetting the whole fmtout... */
    es_format_SetMeta( &id->decoder_out, &p_dec->fmt_in );

    vlc_mutex_unlock( &id->fifo.lock );

    msg_Dbg( p_obj, "Checking if filter chain %4.4s -> %4.4s is possible",
                 (char *)&p_dec->fmt_out.i_codec, (char*)&p_enc_in->i_codec );
    test_chain = filter_chain_NewVideo( p_obj, false, NULL );
    filter_chain_Reset( test_chain, &p_dec->fmt_out, &p_dec->fmt_out );

    int chain_works = filter_chain_AppendConverter( test_chain, p_enc_in );
    filter_chain_Delete( test_chain );

    msg_Dbg( p_obj, "Filter chain testing done, input chroma %4.4s seems to be %s for transcode",
                     (char *)&p_dec->fmt_out.video.i_chroma,
                     chain_works == 0 ? "possible" : "not possible");
    return chain_works;
}