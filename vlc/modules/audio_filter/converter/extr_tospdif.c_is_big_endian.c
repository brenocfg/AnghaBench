#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_format; } ;
struct TYPE_8__ {TYPE_1__ audio; } ;
struct TYPE_9__ {TYPE_2__ fmt_in; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_10__ {int* p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
#define  VLC_CODEC_A52 133 
#define  VLC_CODEC_DTS 132 
#define  VLC_CODEC_DTSHD 131 
#define  VLC_CODEC_EAC3 130 
#define  VLC_CODEC_MLP 129 
#define  VLC_CODEC_TRUEHD 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static bool is_big_endian( filter_t *p_filter, block_t *p_in_buf )
{
    switch( p_filter->fmt_in.audio.i_format )
    {
        case VLC_CODEC_A52:
        case VLC_CODEC_EAC3:
        case VLC_CODEC_MLP:
        case VLC_CODEC_TRUEHD:
            return true;
        case VLC_CODEC_DTS:
        case VLC_CODEC_DTSHD:
            return p_in_buf->p_buffer[0] == 0x1F
                || p_in_buf->p_buffer[0] == 0x7F;
        default:
            vlc_assert_unreachable();
    }
}