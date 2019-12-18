#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_bmask; int /*<<< orphan*/  i_gmask; int /*<<< orphan*/  i_rmask; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_11__ {TYPE_1__ video; int /*<<< orphan*/  i_codec; } ;
struct TYPE_9__ {int /*<<< orphan*/ * p_module; TYPE_7__ fmt_out; TYPE_7__ fmt_in; } ;
typedef  TYPE_2__ vlc_blender_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_bmask; int /*<<< orphan*/  i_gmask; int /*<<< orphan*/  i_rmask; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_3__ video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  es_format_Init (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 

vlc_blender_t *filter_NewBlend( vlc_object_t *p_this,
                           const video_format_t *p_dst_chroma )
{
    vlc_blender_t *p_blend = vlc_custom_create( p_this, sizeof(*p_blend), "blend" );
    if( !p_blend )
        return NULL;

    es_format_Init( &p_blend->fmt_in, VIDEO_ES, 0 );

    es_format_Init( &p_blend->fmt_out, VIDEO_ES, 0 );

    p_blend->fmt_out.i_codec        =
    p_blend->fmt_out.video.i_chroma = p_dst_chroma->i_chroma;
    p_blend->fmt_out.video.i_rmask  = p_dst_chroma->i_rmask;
    p_blend->fmt_out.video.i_gmask  = p_dst_chroma->i_gmask;
    p_blend->fmt_out.video.i_bmask  = p_dst_chroma->i_bmask;

    /* The blend module will be loaded when needed with the real
    * input format */
    p_blend->p_module = NULL;

    return p_blend;
}