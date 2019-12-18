#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_25__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_13__ ;

/* Type definitions */
struct TYPE_32__ {scalar_t__ i_chroma; scalar_t__ i_width; scalar_t__ i_height; } ;
typedef  TYPE_3__ video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_33__ {int /*<<< orphan*/  p_parent; TYPE_6__* p_enc; TYPE_8__* p_converter; } ;
typedef  TYPE_4__ image_handler_t ;
struct TYPE_34__ {TYPE_3__ video; } ;
typedef  TYPE_5__ es_format_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_30__ {scalar_t__ i_chroma; scalar_t__ i_width; scalar_t__ i_height; } ;
struct TYPE_37__ {TYPE_25__ video; } ;
struct TYPE_36__ {int /*<<< orphan*/ * (* pf_video_filter ) (TYPE_8__*,int /*<<< orphan*/ *) ;TYPE_9__ fmt_out; TYPE_9__ fmt_in; } ;
struct TYPE_28__ {TYPE_25__ video; } ;
struct TYPE_29__ {scalar_t__ i_width; scalar_t__ i_height; } ;
struct TYPE_31__ {scalar_t__ i_codec; TYPE_1__ video; } ;
struct TYPE_35__ {int /*<<< orphan*/ * (* pf_encode_video ) (TYPE_6__*,int /*<<< orphan*/ *) ;TYPE_13__ fmt_in; TYPE_2__ fmt_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BitMapFormatIsSimilar (TYPE_25__*,TYPE_3__ const*) ; 
 TYPE_8__* CreateConverter (int /*<<< orphan*/ ,TYPE_5__*,TYPE_25__*) ; 
 TYPE_6__* CreateEncoder (int /*<<< orphan*/ ,TYPE_3__ const*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  DeleteConverter (TYPE_8__*) ; 
 int /*<<< orphan*/  DeleteEncoder (TYPE_6__*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_9__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_9__*,TYPE_13__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  es_format_InitFromVideo (TYPE_9__*,TYPE_3__ const*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  picture_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *ImageWrite( image_handler_t *p_image, picture_t *p_pic,
                            const video_format_t *p_fmt_in,
                            const video_format_t *p_fmt_out )
{
    block_t *p_block;

    /* Check if we can reuse the current encoder */
    if( p_image->p_enc &&
        ( p_image->p_enc->fmt_out.i_codec != p_fmt_out->i_chroma ||
          p_image->p_enc->fmt_out.video.i_width != p_fmt_out->i_width ||
          p_image->p_enc->fmt_out.video.i_height != p_fmt_out->i_height ) )
    {
        DeleteEncoder( p_image->p_enc );
        p_image->p_enc = 0;
    }

    /* Start an encoder */
    if( !p_image->p_enc )
    {
        p_image->p_enc = CreateEncoder( p_image->p_parent,
                                        p_fmt_in, p_fmt_out );
        if( !p_image->p_enc ) return NULL;
    }

    /* Check if we need chroma conversion or resizing */
    if( p_image->p_enc->fmt_in.video.i_chroma != p_fmt_in->i_chroma ||
        p_image->p_enc->fmt_in.video.i_width != p_fmt_in->i_width ||
        p_image->p_enc->fmt_in.video.i_height != p_fmt_in->i_height ||
       !BitMapFormatIsSimilar( &p_image->p_enc->fmt_in.video, p_fmt_in ) )
    {
        picture_t *p_tmp_pic;

        if( p_image->p_converter &&
            ( p_image->p_converter->fmt_in.video.i_chroma != p_fmt_in->i_chroma ||
              p_image->p_converter->fmt_out.video.i_chroma !=
              p_image->p_enc->fmt_in.video.i_chroma ||
             !BitMapFormatIsSimilar( &p_image->p_converter->fmt_in.video, p_fmt_in ) ) )
        {
            /* We need to restart a new filter */
            DeleteConverter( p_image->p_converter );
            p_image->p_converter = NULL;
        }

        /* Start a filter */
        if( !p_image->p_converter )
        {
            es_format_t fmt_in;
            es_format_Init( &fmt_in, VIDEO_ES, p_fmt_in->i_chroma );
            fmt_in.video = *p_fmt_in;

            p_image->p_converter =
                CreateConverter( p_image->p_parent, &fmt_in,
                              &p_image->p_enc->fmt_in.video );

            if( !p_image->p_converter )
            {
                return NULL;
            }
        }
        else
        {
            /* Filters should handle on-the-fly size changes */
            es_format_Clean( &p_image->p_converter->fmt_in );
            es_format_InitFromVideo( &p_image->p_converter->fmt_in, p_fmt_in );
            es_format_Clean( &p_image->p_converter->fmt_out );
            es_format_Copy( &p_image->p_converter->fmt_out, &p_image->p_enc->fmt_in );
        }

        picture_Hold( p_pic );

        p_tmp_pic =
            p_image->p_converter->pf_video_filter( p_image->p_converter, p_pic );

        if( likely(p_tmp_pic != NULL) )
        {
            p_block = p_image->p_enc->pf_encode_video( p_image->p_enc,
                                                       p_tmp_pic );
            picture_Release( p_tmp_pic );
        }
        else
            p_block = NULL;
    }
    else
    {
        p_block = p_image->p_enc->pf_encode_video( p_image->p_enc, p_pic );
    }

    if( !p_block )
    {
        msg_Dbg( p_image->p_parent, "no image encoded" );
        return 0;
    }

    return p_block;
}