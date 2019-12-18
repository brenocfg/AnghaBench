#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int i_format; } ;
struct TYPE_21__ {TYPE_2__ audio; } ;
struct TYPE_23__ {TYPE_1__ fmt_in; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_24__ {TYPE_5__* p_out_buf; int /*<<< orphan*/  i_out_offset; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_25__ {int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  Flush (TYPE_3__*) ; 
#define  SPDIF_ERROR 136 
#define  SPDIF_MORE_DATA 135 
#define  SPDIF_SUCCESS 134 
#define  VLC_CODEC_A52 133 
#define  VLC_CODEC_DTS 132 
#define  VLC_CODEC_DTSHD 131 
#define  VLC_CODEC_EAC3 130 
#define  VLC_CODEC_MLP 129 
#define  VLC_CODEC_TRUEHD 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int write_buffer_ac3 (TYPE_3__*,TYPE_5__*) ; 
 int write_buffer_dts (TYPE_3__*,TYPE_5__*) ; 
 int write_buffer_dtshd (TYPE_3__*,TYPE_5__*) ; 
 int write_buffer_eac3 (TYPE_3__*,TYPE_5__*) ; 
 int write_buffer_truehd (TYPE_3__*,TYPE_5__*) ; 

__attribute__((used)) static block_t *DoWork( filter_t *p_filter, block_t *p_in_buf )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    block_t *p_out_buf = NULL;

    int i_ret;
    switch( p_filter->fmt_in.audio.i_format )
    {
        case VLC_CODEC_A52:
            i_ret = write_buffer_ac3( p_filter, p_in_buf );
            break;
        case VLC_CODEC_EAC3:
            i_ret = write_buffer_eac3( p_filter, p_in_buf );
            break;
        case VLC_CODEC_MLP:
        case VLC_CODEC_TRUEHD:
            i_ret = write_buffer_truehd( p_filter, p_in_buf );
            break;
        case VLC_CODEC_DTSHD:
            i_ret = write_buffer_dtshd( p_filter, p_in_buf );
            break;
        case VLC_CODEC_DTS:
            i_ret = write_buffer_dts( p_filter, p_in_buf );
            break;
        default:
            vlc_assert_unreachable();
    }

    switch( i_ret )
    {
        case SPDIF_SUCCESS:
            assert( p_sys->p_out_buf->i_buffer == p_sys->i_out_offset );
            p_out_buf = p_sys->p_out_buf;
            p_sys->p_out_buf = NULL;
            break;
        case SPDIF_MORE_DATA:
            break;
        case SPDIF_ERROR:
            Flush( p_filter );
            break;
    }

    block_Release( p_in_buf );
    return p_out_buf;
}