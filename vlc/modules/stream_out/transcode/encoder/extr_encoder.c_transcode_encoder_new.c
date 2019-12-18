#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_13__ {int /*<<< orphan*/  lock_out; TYPE_3__* p_encoder; int /*<<< orphan*/  pp_pics; } ;
typedef  TYPE_1__ transcode_encoder_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_cat; int /*<<< orphan*/  i_group; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_16__ {scalar_t__ psz_language; int /*<<< orphan*/  i_group; int /*<<< orphan*/  i_id; } ;
struct TYPE_15__ {TYPE_8__ fmt_out; TYPE_8__ fmt_in; int /*<<< orphan*/ * p_module; } ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_8__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_8__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_fifo_New () ; 
 TYPE_3__* sout_EncoderCreate (int /*<<< orphan*/ *) ; 
 scalar_t__ strdup (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_3__*) ; 

transcode_encoder_t * transcode_encoder_new( vlc_object_t *p_obj,
                                             const es_format_t *p_fmt )
{
    switch( p_fmt->i_cat )
    {
        case VIDEO_ES:
        case AUDIO_ES:
        case SPU_ES:
            break;
        default:
            return NULL;
    }

    transcode_encoder_t *p_enc = calloc( 1, sizeof(*p_enc) );
    if( !p_enc )
        return NULL;

    p_enc->p_encoder = sout_EncoderCreate( p_obj );
    if( !p_enc->p_encoder )
    {
        free( p_enc );
        return NULL;
    }
    p_enc->p_encoder->p_module = NULL;

    /* Create destination format */
    es_format_Init( &p_enc->p_encoder->fmt_in, p_fmt->i_cat, 0 );
    es_format_Copy( &p_enc->p_encoder->fmt_in, p_fmt );
    es_format_Init( &p_enc->p_encoder->fmt_out, p_fmt->i_cat, 0 );
    p_enc->p_encoder->fmt_out.i_id    = p_fmt->i_id;
    p_enc->p_encoder->fmt_out.i_group = p_fmt->i_group;
    if( p_enc->p_encoder->fmt_in.psz_language )
        p_enc->p_encoder->fmt_out.psz_language = strdup( p_enc->p_encoder->fmt_in.psz_language );

    switch( p_fmt->i_cat )
    {
        case VIDEO_ES:
            p_enc->pp_pics = picture_fifo_New();
            if( !p_enc->pp_pics )
            {
                es_format_Clean( &p_enc->p_encoder->fmt_in );
                es_format_Clean( &p_enc->p_encoder->fmt_out );
                vlc_object_delete(p_enc->p_encoder);
                free( p_enc );
                return NULL;
            }
            vlc_mutex_init( &p_enc->lock_out );
            break;
        default:
            break;
    }

    return p_enc;
}