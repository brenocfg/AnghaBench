#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {TYPE_8__* p_sys; } ;
typedef  TYPE_7__ video_splitter_t ;
struct TYPE_32__ {int i_row; int i_col; int /*<<< orphan*/ * lambdah; int /*<<< orphan*/ * lambdav; int /*<<< orphan*/ * p_lut; TYPE_6__* p_chroma; TYPE_11__** pp_output; } ;
typedef  TYPE_8__ video_splitter_sys_t ;
struct TYPE_33__ {int const i_pitch; int const i_pixel_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_9__ plane_t ;
struct TYPE_22__ {int i_planes; TYPE_9__* p; } ;
typedef  TYPE_10__ picture_t ;
struct TYPE_28__ {int const i_right; int const i_left; int const i_top; int const i_bottom; } ;
struct TYPE_26__ {int const i_right; int const i_left; int const i_top; int const i_bottom; } ;
struct TYPE_29__ {TYPE_4__ attenuate; TYPE_2__ black; } ;
struct TYPE_23__ {size_t i_output; int const i_src_x; int const i_src_y; int const i_src_width; int const i_src_height; TYPE_5__ filter; int /*<<< orphan*/  b_active; } ;
typedef  TYPE_11__ panoramix_output_t ;
struct TYPE_27__ {int i_right; int i_left; int i_top; int i_bottom; } ;
struct TYPE_25__ {int i_right; int i_left; int i_top; int i_bottom; } ;
struct TYPE_24__ {TYPE_3__ attenuate; TYPE_1__ black; } ;
typedef  TYPE_12__ panoramix_filter_t ;
struct TYPE_30__ {int* pi_div_w; int* pi_div_h; int /*<<< orphan*/ * pi_black; int /*<<< orphan*/  b_planar; } ;

/* Variables and functions */
 int /*<<< orphan*/  FilterPlanar (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int const,int const,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_CopyProperties (TYPE_10__*,TYPE_10__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_10__*) ; 
 scalar_t__ video_splitter_NewPicture (TYPE_7__*,TYPE_10__**) ; 

__attribute__((used)) static int Filter( video_splitter_t *p_splitter, picture_t *pp_dst[], picture_t *p_src )
{
    video_splitter_sys_t *p_sys = p_splitter->p_sys;

    if( video_splitter_NewPicture( p_splitter, pp_dst ) )
    {
        picture_Release( p_src );
        return VLC_EGENERIC;
    }

    for( int y = 0; y < p_sys->i_row; y++ )
    {
        for( int x = 0; x < p_sys->i_col; x++ )
        {
            const panoramix_output_t *p_output = &p_sys->pp_output[x][y];
            if( !p_output->b_active )
                continue;

            /* */
            picture_t *p_dst = pp_dst[p_output->i_output];

            /* */
            picture_CopyProperties( p_dst, p_src );

            /* */
            for( int i_plane = 0; i_plane < p_src->i_planes; i_plane++ )
            {
                const int i_div_w = p_sys->p_chroma->pi_div_w[i_plane];
                const int i_div_h = p_sys->p_chroma->pi_div_h[i_plane];

                if( !i_div_w || !i_div_h )
                    continue;

                const plane_t *p_srcp = &p_src->p[i_plane];
                const plane_t *p_dstp = &p_dst->p[i_plane];

                /* */
                panoramix_filter_t filter;
                filter.black.i_right  = p_output->filter.black.i_right / i_div_w;
                filter.black.i_left   = p_output->filter.black.i_left / i_div_w;
                filter.black.i_top    = p_output->filter.black.i_top / i_div_h;
                filter.black.i_bottom = p_output->filter.black.i_bottom / i_div_h;

                filter.attenuate.i_right  = p_output->filter.attenuate.i_right / i_div_w;
                filter.attenuate.i_left   = p_output->filter.attenuate.i_left / i_div_w;
                filter.attenuate.i_top    = p_output->filter.attenuate.i_top / i_div_h;
                filter.attenuate.i_bottom = p_output->filter.attenuate.i_bottom / i_div_h;

                /* */
                const int i_x = p_output->i_src_x/i_div_w;
                const int i_y = p_output->i_src_y/i_div_h;

                assert( p_sys->p_chroma->b_planar );
                FilterPlanar( p_dstp->p_pixels, p_dstp->i_pitch,
                              &p_srcp->p_pixels[i_y * p_srcp->i_pitch + i_x * p_srcp->i_pixel_pitch], p_srcp->i_pitch,
                              p_output->i_src_width/i_div_w, p_output->i_src_height/i_div_h,
                              p_sys->p_chroma->pi_black[i_plane],
                              &filter,
                              p_sys->p_lut[i_plane],
                              p_sys->lambdav[i_plane],
                              p_sys->lambdah[i_plane] );
            }
        }
    }

    picture_Release( p_src );
    return VLC_SUCCESS;
}