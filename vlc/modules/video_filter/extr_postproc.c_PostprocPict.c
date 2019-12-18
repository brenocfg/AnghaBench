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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {int i_planes; TYPE_1__* p; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_19__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_20__ {TYPE_2__ video; } ;
struct TYPE_22__ {TYPE_3__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_23__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pp_context; int /*<<< orphan*/ * pp_mode; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_18__ {int i_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 TYPE_4__* CopyInfoAndRelease (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* filter_NewPicture (TYPE_5__*) ; 
 int /*<<< orphan*/  picture_CopyPixels (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  pp_postprocess (int /*<<< orphan*/  const**,int*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *PostprocPict( filter_t *p_filter, picture_t *p_pic )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    picture_t *p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        picture_Release( p_pic );
        return NULL;
    }

    /* Lock to prevent issues if pp_mode is changed */
    vlc_mutex_lock( &p_sys->lock );
    if( p_sys->pp_mode != NULL )
    {
        const uint8_t *src[3];
        uint8_t *dst[3];
        int i_src_stride[3], i_dst_stride[3];

        for( int i_plane = 0; i_plane < p_pic->i_planes; i_plane++ )
        {
            src[i_plane] = p_pic->p[i_plane].p_pixels;
            dst[i_plane] = p_outpic->p[i_plane].p_pixels;

            /* I'm not sure what happens if i_pitch != i_visible_pitch ...
             * at least it shouldn't crash. */
            i_src_stride[i_plane] = p_pic->p[i_plane].i_pitch;
            i_dst_stride[i_plane] = p_outpic->p[i_plane].i_pitch;
        }

        pp_postprocess( src, i_src_stride, dst, i_dst_stride,
                        p_filter->fmt_in.video.i_width,
                        p_filter->fmt_in.video.i_height, NULL, 0,
                        p_sys->pp_mode, p_sys->pp_context, 0 );
    }
    else
        picture_CopyPixels( p_outpic, p_pic );
    vlc_mutex_unlock( &p_sys->lock );

    return CopyInfoAndRelease( p_outpic, p_pic );
}