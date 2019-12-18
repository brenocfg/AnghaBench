#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ i_visible_width; scalar_t__ i_visible_height; scalar_t__ i_width; scalar_t__ i_height; scalar_t__ i_y_offset; scalar_t__ i_x_offset; } ;
typedef  TYPE_3__ video_format_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_23__ {int /*<<< orphan*/  lock; } ;
struct TYPE_22__ {int /*<<< orphan*/  video; } ;
struct TYPE_25__ {TYPE_5__* p_spu_blender; int /*<<< orphan*/  p_spu; int /*<<< orphan*/  encoder; int /*<<< orphan*/  p_f_chain; TYPE_2__ fifo; TYPE_1__ decoder_out; } ;
typedef  TYPE_4__ sout_stream_id_sys_t ;
struct TYPE_26__ {int /*<<< orphan*/  date; int /*<<< orphan*/  format; } ;
typedef  TYPE_5__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_5__* filter_NewBlend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ filter_chain_IsEmpty (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (TYPE_5__*) ; 
 int /*<<< orphan*/  picture_BlendSubpicture (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Copy (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_5__*) ; 
 int /*<<< orphan*/ * spu_Render (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  subpicture_Delete (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* video_new_buffer_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static picture_t * RenderSubpictures( sout_stream_t *p_stream, sout_stream_id_sys_t *id,
                                       picture_t *p_pic )
{
    VLC_UNUSED(p_stream);

    if( !id->p_spu )
        return p_pic;

    /* Check if we have a subpicture to overlay */
    video_format_t fmt, outfmt;
    vlc_mutex_lock( &id->fifo.lock );
    video_format_Copy( &outfmt, &id->decoder_out.video );
    vlc_mutex_unlock( &id->fifo.lock );
    video_format_Copy( &fmt, &p_pic->format );
    if( fmt.i_visible_width <= 0 || fmt.i_visible_height <= 0 )
    {
        fmt.i_visible_width  = fmt.i_width;
        fmt.i_visible_height = fmt.i_height;
        fmt.i_x_offset       = 0;
        fmt.i_y_offset       = 0;
    }

    subpicture_t *p_subpic = spu_Render( id->p_spu, NULL, &fmt,
                                         &outfmt, vlc_tick_now(), p_pic->date,
                                         false, false );

    /* Overlay subpicture */
    if( p_subpic )
    {
        if( filter_chain_IsEmpty( id->p_f_chain ) )
        {
            /* We can't modify the picture, we need to duplicate it,
                 * in this point the picture is already p_encoder->fmt.in format*/
            picture_t *p_tmp = video_new_buffer_encoder( id->encoder );
            if( likely( p_tmp ) )
            {
                picture_Copy( p_tmp, p_pic );
                picture_Release( p_pic );
                p_pic = p_tmp;
            }
        }
        if( unlikely( !id->p_spu_blender ) )
            id->p_spu_blender = filter_NewBlend( VLC_OBJECT( id->p_spu ), &fmt );
        if( likely( id->p_spu_blender ) )
            picture_BlendSubpicture( p_pic, id->p_spu_blender, p_subpic );
        subpicture_Delete( p_subpic );
    }
    video_format_Clean( &fmt );
    video_format_Clean( &outfmt );

    return p_pic;
}