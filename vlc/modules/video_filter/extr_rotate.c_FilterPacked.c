#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_20__ {TYPE_2__* p; TYPE_1__ format; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_21__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_22__ {int /*<<< orphan*/ * p_motion; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_19__ {int i_visible_pitch; int i_visible_lines; int* p_pixels; int i_pitch; } ;

/* Variables and functions */
 TYPE_3__* CopyInfoAndRelease (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ GetPackedYuvOffsets (int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  fetch_trigo (TYPE_5__*,int*,int*) ; 
 TYPE_3__* filter_NewPicture (TYPE_4__*) ; 
 int motion_get_angle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  store_trigo (TYPE_5__*,int) ; 

__attribute__((used)) static picture_t *FilterPacked( filter_t *p_filter, picture_t *p_pic )
{
    picture_t *p_outpic;
    filter_sys_t *p_sys = p_filter->p_sys;

    if( !p_pic ) return NULL;

    int i_u_offset, i_v_offset, i_y_offset;

    if( GetPackedYuvOffsets( p_pic->format.i_chroma, &i_y_offset,
                             &i_u_offset, &i_v_offset ) != VLC_SUCCESS )
    {
        msg_Warn( p_filter, "Unsupported input chroma (%4.4s)",
                  (char*)&(p_pic->format.i_chroma) );
        picture_Release( p_pic );
        return NULL;
    }

    p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        picture_Release( p_pic );
        return NULL;
    }

    const int i_visible_pitch = p_pic->p->i_visible_pitch>>1; /* In fact it's i_visible_pixels */
    const int i_visible_lines = p_pic->p->i_visible_lines;

    const uint8_t *p_in   = p_pic->p->p_pixels+i_y_offset;
    const uint8_t *p_in_u = p_pic->p->p_pixels+i_u_offset;
    const uint8_t *p_in_v = p_pic->p->p_pixels+i_v_offset;
    const int i_in_pitch  = p_pic->p->i_pitch;

    uint8_t *p_out   = p_outpic->p->p_pixels+i_y_offset;
    uint8_t *p_out_u = p_outpic->p->p_pixels+i_u_offset;
    uint8_t *p_out_v = p_outpic->p->p_pixels+i_v_offset;
    const int i_out_pitch = p_outpic->p->i_pitch;

    const int i_line_center = i_visible_lines>>1;
    const int i_col_center  = i_visible_pitch>>1;

    if( p_sys->p_motion != NULL )
    {
        int i_angle = motion_get_angle( p_sys->p_motion );
        store_trigo( p_sys, i_angle / 20.f );
    }

    int i_sin, i_cos;
    fetch_trigo( p_sys, &i_sin, &i_cos );

    for( int i_line = 0; i_line < i_visible_lines; i_line++ )
    {
        for( int i_col = 0; i_col < i_visible_pitch; i_col++ )
        {
            int i_line_orig;
            int i_col_orig;
            /* Handle "1st Y", U and V */
            i_line_orig = i_line_center +
                ( ( i_sin * ( i_col - i_col_center )
                  + i_cos * ( i_line - i_line_center ) )>>12 );
            i_col_orig = i_col_center +
                ( ( i_cos * ( i_col - i_col_center )
                  - i_sin * ( i_line - i_line_center ) )>>12 );
            if( 0 <= i_col_orig && i_col_orig < i_visible_pitch
             && 0 <= i_line_orig && i_line_orig < i_visible_lines )
            {
                p_out[i_line*i_out_pitch+2*i_col] = p_in[i_line_orig*i_in_pitch+2*i_col_orig];
                i_col_orig /= 2;
                p_out_u[i_line*i_out_pitch+2*i_col] = p_in_u[i_line_orig*i_in_pitch+4*i_col_orig];
                p_out_v[i_line*i_out_pitch+2*i_col] = p_in_v[i_line_orig*i_in_pitch+4*i_col_orig];
            }
            else
            {
                p_out[i_line*i_out_pitch+2*i_col] = 0x00;
                p_out_u[i_line*i_out_pitch+2*i_col] = 0x80;
                p_out_v[i_line*i_out_pitch+2*i_col] = 0x80;
            }

            /* Handle "2nd Y" */
            i_col++;
            if( i_col >= i_visible_pitch )
                break;

            i_line_orig = i_line_center +
                ( ( i_sin * ( i_col - i_col_center )
                  + i_cos * ( i_line - i_line_center ) )>>12 );
            i_col_orig = i_col_center +
                ( ( i_cos * ( i_col - i_col_center )
                  - i_sin * ( i_line - i_line_center ) )>>12 );
            if( 0 <= i_col_orig && i_col_orig < i_visible_pitch
             && 0 <= i_line_orig && i_line_orig < i_visible_lines )
            {
                p_out[i_line*i_out_pitch+2*i_col] = p_in[i_line_orig*i_in_pitch+2*i_col_orig];
            }
            else
            {
                p_out[i_line*i_out_pitch+2*i_col] = 0x00;
            }
        }
    }

    return CopyInfoAndRelease( p_outpic, p_pic );
}