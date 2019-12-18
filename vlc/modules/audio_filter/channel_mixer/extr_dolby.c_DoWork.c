#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  audio; } ;
struct TYPE_11__ {TYPE_1__ fmt_out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_12__ {scalar_t__ i_rear_left; scalar_t__ i_rear_center; scalar_t__ i_rear_right; scalar_t__ i_center; size_t i_left; size_t i_right; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_13__ {size_t i_nb_samples; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; scalar_t__ p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 size_t aout_FormatNbChannels (int /*<<< orphan*/ *) ; 
 TYPE_4__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *DoWork( filter_t * p_filter, block_t * p_in_buf )
{
    filter_sys_t * p_sys = p_filter->p_sys;
    float * p_in = (float*) p_in_buf->p_buffer;
    size_t i_nb_samples = p_in_buf->i_nb_samples;
    size_t i_nb_channels = aout_FormatNbChannels( &p_filter->fmt_out.audio );
    size_t i_nb_rear = 0;
    size_t i;
    block_t *p_out_buf = block_Alloc(
                                sizeof(float) * i_nb_samples * i_nb_channels );
    if( !p_out_buf )
        goto out;

    float * p_out = (float*) p_out_buf->p_buffer;
    p_out_buf->i_nb_samples = i_nb_samples;
    p_out_buf->i_dts        = p_in_buf->i_dts;
    p_out_buf->i_pts        = p_in_buf->i_pts;
    p_out_buf->i_length     = p_in_buf->i_length;

    memset( p_out, 0, p_out_buf->i_buffer );

    if( p_sys->i_rear_left >= 0 )
    {
        ++i_nb_rear;
    }
    if( p_sys->i_rear_center >= 0 )
    {
        ++i_nb_rear;
    }
    if( p_sys->i_rear_right >= 0 )
    {
        ++i_nb_rear;
    }

    for( i = 0; i < i_nb_samples; ++i )
    {
        float f_left = p_in[ i * 2 ];
        float f_right = p_in[ i * 2 + 1 ];
        float f_rear = ( f_left - f_right ) / i_nb_rear;

        if( p_sys->i_center >= 0 )
        {
            float f_center = f_left + f_right;
            f_left -= f_center / 2;
            f_right -= f_center / 2;

            p_out[ i * i_nb_channels + p_sys->i_center ] = f_center;
        }

        if( p_sys->i_left >= 0 )
        {
            p_out[ i * i_nb_channels + p_sys->i_left ] = f_left;
        }
        if( p_sys->i_right >= 0 )
        {
            p_out[ i * i_nb_channels + p_sys->i_right ] = f_right;
        }
        if( p_sys->i_rear_left >= 0 )
        {
            p_out[ i * i_nb_channels + p_sys->i_rear_left ] = f_rear;
        }
        if( p_sys->i_rear_center >= 0 )
        {
            p_out[ i * i_nb_channels + p_sys->i_rear_center ] = f_rear;
        }
        if( p_sys->i_rear_right >= 0 )
        {
            p_out[ i * i_nb_channels + p_sys->i_rear_right ] = f_rear;
        }
    }
out:
    block_Release( p_in_buf );
    return p_out_buf;
}