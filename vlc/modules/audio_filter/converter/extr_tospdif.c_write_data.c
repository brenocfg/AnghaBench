#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {scalar_t__ i_format; } ;
struct TYPE_9__ {TYPE_1__ audio; } ;
struct TYPE_11__ {TYPE_2__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_12__ {size_t i_out_offset; TYPE_3__* p_out_buf; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_10__ {int* p_buffer; size_t i_buffer; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_SPDIFB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  set_16 (TYPE_4__*,int*,int const) ; 
 int /*<<< orphan*/  swab (int const*,int*,size_t) ; 

__attribute__((used)) static void write_data( filter_t *p_filter, const void *p_buf, size_t i_size,
                        bool b_input_big_endian )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    assert( p_sys->p_out_buf != NULL );

    bool b_output_big_endian =
        p_filter->fmt_out.audio.i_format == VLC_CODEC_SPDIFB;
    uint8_t *p_out = &p_sys->p_out_buf->p_buffer[p_sys->i_out_offset];
    const uint8_t *p_in = p_buf;

    assert( p_sys->p_out_buf->i_buffer - p_sys->i_out_offset >= i_size );

    if( b_input_big_endian != b_output_big_endian )
        swab( p_in, p_out, i_size & ~1 );
    else
        memcpy( p_out, p_in, i_size & ~1 );
    p_sys->i_out_offset += ( i_size & ~1 );

    if( i_size & 1 )
    {
        assert( p_sys->p_out_buf->i_buffer - p_sys->i_out_offset >= 2 );
        p_out += ( i_size & ~1 );
        set_16( p_filter, p_out, p_in[i_size - 1] << 8 );
        p_sys->i_out_offset += 2;
    }
}