#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int i_pitch; int i_visible_lines; int /*<<< orphan*/  i_visible_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_13__ {int i_planes; TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_14__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_3__ filter_t ;
typedef  int /*<<< orphan*/  filter_sys_t ;
typedef  scalar_t__ compose_chroma_t ;

/* Variables and functions */
 scalar_t__ CC_ALTLINE ; 
 scalar_t__ CC_MERGE ; 
 scalar_t__ CC_SOURCE_BOTTOM ; 
 scalar_t__ CC_SOURCE_TOP ; 
 scalar_t__ CC_UPCONVERT ; 
 int /*<<< orphan*/  EndMerge () ; 
 int FFMIN3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FieldFromPlane (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int U_PLANE ; 
 int V_PLANE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  plane_CopyPixels (TYPE_1__*,TYPE_1__*) ; 

void ComposeFrame( filter_t *p_filter,
                   picture_t *p_outpic,
                   picture_t *p_inpic_top, picture_t *p_inpic_bottom,
                   compose_chroma_t i_output_chroma, bool swapped_uv_conversion )
{
    assert( p_outpic != NULL );
    assert( p_inpic_top != NULL );
    assert( p_inpic_bottom != NULL );

    /* Valid 4:2:0 chroma handling modes. */
    assert( i_output_chroma == CC_ALTLINE       ||
            i_output_chroma == CC_UPCONVERT     ||
            i_output_chroma == CC_SOURCE_TOP    ||
            i_output_chroma == CC_SOURCE_BOTTOM ||
            i_output_chroma == CC_MERGE );

    filter_sys_t *p_sys = p_filter->p_sys;

    const bool b_upconvert_chroma = i_output_chroma == CC_UPCONVERT;

    for( int i_plane = 0 ; i_plane < p_inpic_top->i_planes ; i_plane++ )
    {
        bool b_is_chroma_plane = ( i_plane == U_PLANE || i_plane == V_PLANE );

        int i_out_plane;
        if( b_is_chroma_plane  &&  b_upconvert_chroma  && swapped_uv_conversion )
        {
            if( i_plane == U_PLANE )
                i_out_plane = V_PLANE;
            else /* V_PLANE */
                i_out_plane = U_PLANE;
        }
        else
        {
            i_out_plane = i_plane;
        }

        /* Copy luma or chroma, alternating between input fields. */
        if( !b_is_chroma_plane  ||  i_output_chroma == CC_ALTLINE )
        {
            /* Do an alternating line copy. This is always done for luma,
               and for 4:2:2 chroma. It can be requested for 4:2:0 chroma
               using CC_ALTLINE (see function doc).

               Note that when we get here, the number of lines matches
               in input and output.
            */
            plane_t dst_top;
            plane_t dst_bottom;
            plane_t src_top;
            plane_t src_bottom;
            FieldFromPlane( &dst_top,    &p_outpic->p[i_out_plane],   0 );
            FieldFromPlane( &dst_bottom, &p_outpic->p[i_out_plane],   1 );
            FieldFromPlane( &src_top,    &p_inpic_top->p[i_plane],    0 );
            FieldFromPlane( &src_bottom, &p_inpic_bottom->p[i_plane], 1 );

            /* Copy each field from the corresponding source. */
            plane_CopyPixels( &dst_top,    &src_top    );
            plane_CopyPixels( &dst_bottom, &src_bottom );
        }
        else /* Input 4:2:0, on a chroma plane, and not in altline mode. */
        {
            if( i_output_chroma == CC_UPCONVERT )
            {
                /* Upconverting copy - use all data from both input fields.

                   This produces an output picture with independent chroma
                   for each field. It can be used for general input when
                   the two input frames are different.

                   The output is 4:2:2, but the input is 4:2:0. Thus the output
                   has twice the lines of the input, and each full chroma plane
                   in the input corresponds to a field chroma plane in the
                   output.
                */
                plane_t dst_top;
                plane_t dst_bottom;
                FieldFromPlane( &dst_top,    &p_outpic->p[i_out_plane], 0 );
                FieldFromPlane( &dst_bottom, &p_outpic->p[i_out_plane], 1 );

                /* Copy each field from the corresponding source. */
                plane_CopyPixels( &dst_top,    &p_inpic_top->p[i_plane]    );
                plane_CopyPixels( &dst_bottom, &p_inpic_bottom->p[i_plane] );
            }
            else if( i_output_chroma == CC_SOURCE_TOP )
            {
                /* Copy chroma of input top field. Ignore chroma of input
                   bottom field. Input and output are both 4:2:0, so we just
                   copy the whole plane. */
                plane_CopyPixels( &p_outpic->p[i_out_plane],
                                  &p_inpic_top->p[i_plane] );
            }
            else if( i_output_chroma == CC_SOURCE_BOTTOM )
            {
                /* Copy chroma of input bottom field. Ignore chroma of input
                   top field. Input and output are both 4:2:0, so we just
                   copy the whole plane. */
                plane_CopyPixels( &p_outpic->p[i_out_plane],
                                  &p_inpic_bottom->p[i_plane] );
            }
            else /* i_output_chroma == CC_MERGE */
            {
                /* Average the chroma of the input fields.
                   Input and output are both 4:2:0. */
                uint8_t *p_in_top, *p_in_bottom, *p_out_end, *p_out;
                p_in_top    = p_inpic_top->p[i_plane].p_pixels;
                p_in_bottom = p_inpic_bottom->p[i_plane].p_pixels;
                p_out = p_outpic->p[i_out_plane].p_pixels;
                p_out_end = p_out + p_outpic->p[i_out_plane].i_pitch
                                  * p_outpic->p[i_out_plane].i_visible_lines;

                int w = FFMIN3( p_inpic_top->p[i_plane].i_visible_pitch,
                                p_inpic_bottom->p[i_plane].i_visible_pitch,
                                p_outpic->p[i_plane].i_visible_pitch );

                for( ; p_out < p_out_end ; )
                {
                    Merge( p_out, p_in_top, p_in_bottom, w );
                    p_out       += p_outpic->p[i_out_plane].i_pitch;
                    p_in_top    += p_inpic_top->p[i_plane].i_pitch;
                    p_in_bottom += p_inpic_bottom->p[i_plane].i_pitch;
                }
                EndMerge();
            }
        }
    }
}