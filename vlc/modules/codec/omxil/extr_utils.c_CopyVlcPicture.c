#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int i_planes; TYPE_3__* p; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_15__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_12__ {int i_frame_stride_chroma_div; } ;
struct TYPE_11__ {int i_frame_stride; } ;
struct TYPE_16__ {TYPE_2__ in; TYPE_1__ out; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_17__ {int nOffset; int /*<<< orphan*/ * pBuffer; } ;
struct TYPE_13__ {int i_pitch; int i_visible_pitch; int i_visible_lines; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_7__ OMX_BUFFERHEADERTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void CopyVlcPicture( decoder_t *p_dec, OMX_BUFFERHEADERTYPE *p_header,
                     picture_t *p_pic)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    int i_src_stride, i_dst_stride;
    int i_plane, i_width, i_line;
    uint8_t *p_dst, *p_src;

    i_dst_stride  = p_sys->out.i_frame_stride;
    p_dst = p_header->pBuffer + p_header->nOffset;

    for( i_plane = 0; i_plane < p_pic->i_planes; i_plane++ )
    {
        if(i_plane == 1) i_dst_stride /= p_sys->in.i_frame_stride_chroma_div;
        p_src = p_pic->p[i_plane].p_pixels;
        i_src_stride = p_pic->p[i_plane].i_pitch;
        i_width = p_pic->p[i_plane].i_visible_pitch;

        for( i_line = 0; i_line < p_pic->p[i_plane].i_visible_lines; i_line++ )
        {
            memcpy( p_dst, p_src, i_width );
            p_src += i_src_stride;
            p_dst += i_dst_stride;
        }
    }
}