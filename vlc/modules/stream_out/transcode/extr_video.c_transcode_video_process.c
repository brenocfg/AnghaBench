#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_58__   TYPE_9__ ;
typedef  struct TYPE_57__   TYPE_8__ ;
typedef  struct TYPE_56__   TYPE_7__ ;
typedef  struct TYPE_55__   TYPE_6__ ;
typedef  struct TYPE_54__   TYPE_5__ ;
typedef  struct TYPE_53__   TYPE_4__ ;
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_32__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_22__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_19__ ;
typedef  struct TYPE_46__   TYPE_11__ ;
typedef  struct TYPE_45__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_45__ {int /*<<< orphan*/  i_chroma; int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; } ;
struct TYPE_55__ {int b_error; int /*<<< orphan*/  encoder; TYPE_22__* p_enccfg; int /*<<< orphan*/ * p_final_conv_static; int /*<<< orphan*/ * p_uf_chain; int /*<<< orphan*/ * p_conv_static; int /*<<< orphan*/ * p_conv_nonstatic; int /*<<< orphan*/ * p_f_chain; scalar_t__ downstream_id; TYPE_32__* p_decoder; scalar_t__ (* pf_transcode_downstream_add ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  p_filterscfg; TYPE_10__ fmt_input_video; int /*<<< orphan*/ * p_spu_blender; } ;
typedef  TYPE_6__ sout_stream_id_sys_t ;
struct TYPE_46__ {int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; } ;
struct TYPE_56__ {TYPE_11__ format; struct TYPE_56__* p_next; } ;
typedef  TYPE_7__ picture_t ;
typedef  int /*<<< orphan*/  filter_chain_t ;
struct TYPE_57__ {TYPE_10__ video; } ;
typedef  TYPE_8__ es_format_t ;
struct TYPE_58__ {int i_flags; } ;
typedef  TYPE_9__ block_t ;
struct TYPE_54__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_48__ {int i_count; } ;
struct TYPE_52__ {scalar_t__ num; } ;
struct TYPE_53__ {TYPE_1__ threads; TYPE_3__ fps; } ;
struct TYPE_50__ {int /*<<< orphan*/  video; } ;
struct TYPE_51__ {int (* pf_decode ) (TYPE_32__*,TYPE_9__*) ;int /*<<< orphan*/  fmt_in; TYPE_2__ fmt_out; } ;
struct TYPE_49__ {char* psz_name; TYPE_4__ video; int /*<<< orphan*/  i_codec; } ;
struct TYPE_47__ {TYPE_5__ video; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int BLOCK_FLAG_END_OF_SEQUENCE ; 
 TYPE_7__* RenderSubpictures (int /*<<< orphan*/ *,TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int VLCDEC_SUCCESS ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_9__**,TYPE_9__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_DeleteBlend (int /*<<< orphan*/ *) ; 
 TYPE_7__* filter_chain_VideoFilter (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  filtered_video_format (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_7__*) ; 
 int stub1 (TYPE_32__*,TYPE_9__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag_last_block_with_flag (TYPE_9__**,int) ; 
 TYPE_7__* transcode_dequeue_all_pics (TYPE_6__*) ; 
 int /*<<< orphan*/  transcode_encoder_close (int /*<<< orphan*/ ) ; 
 scalar_t__ transcode_encoder_drain (int /*<<< orphan*/ ,TYPE_9__**) ; 
 TYPE_9__* transcode_encoder_encode (int /*<<< orphan*/ ,TYPE_7__*) ; 
 TYPE_19__* transcode_encoder_format_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_encoder_format_out (int /*<<< orphan*/ ) ; 
 TYPE_9__* transcode_encoder_get_output_async (int /*<<< orphan*/ ) ; 
 scalar_t__ transcode_encoder_open (int /*<<< orphan*/ ,TYPE_22__*) ; 
 scalar_t__ transcode_encoder_opened (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_encoder_video_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_22__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_remove_filters (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  transcode_video_filters_configured (TYPE_6__*) ; 
 scalar_t__ transcode_video_filters_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_8__*,TYPE_19__*,TYPE_6__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_10__*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  video_format_IsSimilar (TYPE_10__*,TYPE_11__*) ; 

int transcode_video_process( sout_stream_t *p_stream, sout_stream_id_sys_t *id,
                                    block_t *in, block_t **out )
{
    *out = NULL;

    bool b_eos = in && (in->i_flags & BLOCK_FLAG_END_OF_SEQUENCE);

    int ret = id->p_decoder->pf_decode( id->p_decoder, in );
    if( ret != VLCDEC_SUCCESS )
        return VLC_EGENERIC;

    picture_t *p_pics = transcode_dequeue_all_pics( id );

    do
    {
        picture_t *p_pic = p_pics;
        if( p_pic )
        {
            p_pics = p_pic->p_next;
            p_pic->p_next = NULL;
        }

        if( id->b_error && p_pic )
        {
            picture_Release( p_pic );
            continue;
        }

        if( p_pic && ( unlikely(!transcode_encoder_opened(id->encoder)) ||
              !video_format_IsSimilar( &id->fmt_input_video, &p_pic->format ) ) )
        {
            if( !transcode_encoder_opened(id->encoder) ) /* Configure Encoder input/output */
            {
                assert( !id->p_f_chain && !id->p_uf_chain );
                transcode_encoder_video_configure( VLC_OBJECT(p_stream),
                                                   &id->p_decoder->fmt_out.video,
                                                   id->p_enccfg,
                                                   filtered_video_format( id, p_pic ),
                                                   id->encoder );
                /* will be opened below */
            }
            else /* picture format has changed */
            {
                msg_Info( p_stream, "aspect-ratio changed, reiniting. %i -> %i : %i -> %i.",
                            id->fmt_input_video.i_sar_num, p_pic->format.i_sar_num,
                            id->fmt_input_video.i_sar_den, p_pic->format.i_sar_den
                        );
                /* Close filters, encoder format input can't change */
                transcode_remove_filters( &id->p_f_chain );
                transcode_remove_filters( &id->p_conv_nonstatic );
                transcode_remove_filters( &id->p_conv_static );
                transcode_remove_filters( &id->p_uf_chain );
                transcode_remove_filters( &id->p_final_conv_static );
                if( id->p_spu_blender )
                    filter_DeleteBlend( id->p_spu_blender );
                id->p_spu_blender = NULL;

                video_format_Clean( &id->fmt_input_video );
            }

            video_format_Copy( &id->fmt_input_video, &p_pic->format );

            if( !transcode_video_filters_configured( id ) )
            {
                es_format_t tmpfmt;
                es_format_Init( &tmpfmt, VIDEO_ES, id->fmt_input_video.i_chroma );
                tmpfmt.video = id->fmt_input_video;
                if( transcode_video_filters_init( p_stream,
                                                  id->p_filterscfg,
                                                 (id->p_enccfg->video.fps.num > 0),
                                                 &tmpfmt,
                                                 transcode_encoder_format_in( id->encoder ),
                                                 id ) != VLC_SUCCESS )
                    goto error;
            }

            /* Start missing encoder */
            if( !transcode_encoder_opened( id->encoder ) &&
                transcode_encoder_open( id->encoder, id->p_enccfg ) != VLC_SUCCESS )
            {
                msg_Err( p_stream, "cannot find video encoder (module:%s fourcc:%4.4s). "
                                   "Take a look few lines earlier to see possible reason.",
                                   id->p_enccfg->psz_name ? id->p_enccfg->psz_name : "any",
                                   (char *)&id->p_enccfg->i_codec );
                goto error;
            }

            msg_Dbg( p_stream, "destination (after video filters) %ux%u",
                               transcode_encoder_format_in( id->encoder )->video.i_width,
                               transcode_encoder_format_in( id->encoder )->video.i_height );

            if( !id->downstream_id )
                id->downstream_id =
                    id->pf_transcode_downstream_add( p_stream,
                                                     &id->p_decoder->fmt_in,
                                                     transcode_encoder_format_out( id->encoder ) );
            if( !id->downstream_id )
            {
                msg_Err( p_stream, "cannot output transcoded stream %4.4s",
                                   (char *) &id->p_enccfg->i_codec );
                goto error;
            }
        }

        /* Run the filter and output chains; first with the picture,
         * and then with NULL as many times as we need until they
         * stop outputting frames.
         */
        for ( picture_t *p_in = p_pic; ; p_in = NULL /* drain second time */ )
        {
            /* Run filter chain */
            filter_chain_t * primary_chains[] = { id->p_f_chain,
                                                  id->p_conv_nonstatic,
                                                  id->p_conv_static };
            for( size_t i=0; p_in && i<ARRAY_SIZE(primary_chains); i++ )
            {
                if( !primary_chains[i] )
                    continue;
                p_in = filter_chain_VideoFilter( primary_chains[i], p_in );
            }

            if( !p_in )
                break;

            for ( ;; p_in = NULL /* drain second time */ )
            {
                /* Run user specified filter chain */
                filter_chain_t * secondary_chains[] = { id->p_uf_chain,
                                                        id->p_final_conv_static };
                for( size_t i=0; p_in && i<ARRAY_SIZE(secondary_chains); i++ )
                {
                    if( !secondary_chains[i] )
                        continue;
                    p_in = filter_chain_VideoFilter( secondary_chains[i], p_in );
                }

                if( !p_in )
                    break;

                /* Blend subpictures */
                p_in = RenderSubpictures( p_stream, id, p_in );

                if( p_in )
                {
                    block_t *p_encoded = transcode_encoder_encode( id->encoder, p_in );
                    if( p_encoded )
                        block_ChainAppend( out, p_encoded );
                    picture_Release( p_in );
                }
            }
        }

        if( b_eos )
        {
            msg_Info( p_stream, "Drain/restart on EOS" );
            if( transcode_encoder_drain( id->encoder, out ) != VLC_SUCCESS )
                goto error;
            transcode_encoder_close( id->encoder );
            /* Close filters */
            transcode_remove_filters( &id->p_f_chain );
            transcode_remove_filters( &id->p_conv_nonstatic );
            transcode_remove_filters( &id->p_conv_static );
            transcode_remove_filters( &id->p_uf_chain );
            transcode_remove_filters( &id->p_final_conv_static );
            tag_last_block_with_flag( out, BLOCK_FLAG_END_OF_SEQUENCE );
            b_eos = false;
        }

        continue;
error:
        if( p_pic )
            picture_Release( p_pic );
        id->b_error = true;
    } while( p_pics );

    if( id->p_enccfg->video.threads.i_count >= 1 )
    {
        /* Pick up any return data the encoder thread wants to output. */
        block_ChainAppend( out, transcode_encoder_get_output_async( id->encoder ) );
    }

    /* Drain encoder */
    if( unlikely( !id->b_error && in == NULL ) && transcode_encoder_opened( id->encoder ) )
    {
        msg_Dbg( p_stream, "Flushing thread and waiting that");
        if( transcode_encoder_drain( id->encoder, out ) == VLC_SUCCESS )
            msg_Dbg( p_stream, "Flushing done");
        else
            msg_Warn( p_stream, "Flushing failed");
    }

    if( b_eos )
        tag_last_block_with_flag( out, BLOCK_FLAG_END_OF_SEQUENCE );

    return id->b_error ? VLC_EGENERIC : VLC_SUCCESS;
}