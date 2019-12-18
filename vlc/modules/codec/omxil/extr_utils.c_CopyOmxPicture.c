#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_10__ {int i_planes; TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
typedef  int /*<<< orphan*/  copy_cache_t ;
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_9__ {int i_pitch; int i_visible_pitch; int i_visible_lines; int /*<<< orphan*/  const* p_pixels; } ;
typedef  TYPE_3__ ArchitectureSpecificCopyData ;

/* Variables and functions */
 int /*<<< orphan*/  Copy420_SP_to_P (TYPE_2__*,int /*<<< orphan*/  const**,size_t const*,int,int /*<<< orphan*/ *) ; 
 int OMX_COLOR_FormatYUV420SemiPlanar ; 
 int QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  picture_SwapUV (TYPE_2__*) ; 
 int /*<<< orphan*/  qcom_convert (int /*<<< orphan*/  const*,TYPE_2__*) ; 
 scalar_t__ vlc_CPU_SSE2 () ; 

void CopyOmxPicture( int i_color_format, picture_t *p_pic,
                     int i_slice_height,
                     int i_src_stride, uint8_t *p_src, int i_chroma_div,
                     ArchitectureSpecificCopyData *p_architecture_specific )
{
    uint8_t *p_dst;
    int i_dst_stride;
    int i_plane, i_width, i_line;
    if( i_color_format == QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka )
    {
        qcom_convert(p_src, p_pic);
        return;
    }
#ifdef CAN_COMPILE_SSE2
    if( i_color_format == OMX_COLOR_FormatYUV420SemiPlanar
        && vlc_CPU_SSE2() && p_architecture_specific && p_architecture_specific->data )
    {
        copy_cache_t *p_surface_cache = (copy_cache_t*)p_architecture_specific->data;
        const uint8_t *ppi_src_pointers[2] = { p_src, p_src + i_src_stride * i_slice_height };
        const size_t pi_src_strides[2] = { i_src_stride, i_src_stride };
        Copy420_SP_to_P( p_pic, ppi_src_pointers, pi_src_strides,
                         i_slice_height, p_surface_cache );
        picture_SwapUV( p_pic );
        return;
    }
#endif

    for( i_plane = 0; i_plane < p_pic->i_planes; i_plane++ )
    {
        if(i_plane == 1) i_src_stride /= i_chroma_div;
        p_dst = p_pic->p[i_plane].p_pixels;
        i_dst_stride = p_pic->p[i_plane].i_pitch;
        i_width = p_pic->p[i_plane].i_visible_pitch;

        for( i_line = 0; i_line < p_pic->p[i_plane].i_visible_lines; i_line++ )
        {
            memcpy( p_dst, p_src, i_width );
            p_src += i_src_stride;
            p_dst += i_dst_stride;
        }
        /* Handle plane height, which may be indicated via nSliceHeight in OMX.
         * The handling for chroma planes currently assumes vertically
         * subsampled chroma, e.g. 422 planar wouldn't work right. */
        if( i_plane == 0 && i_slice_height > p_pic->p[i_plane].i_visible_lines )
            p_src += i_src_stride * (i_slice_height - p_pic->p[i_plane].i_visible_lines);
        else if ( i_plane > 0 && i_slice_height/2 > p_pic->p[i_plane].i_visible_lines )
            p_src += i_src_stride * (i_slice_height/2 - p_pic->p[i_plane].i_visible_lines);
    }
}