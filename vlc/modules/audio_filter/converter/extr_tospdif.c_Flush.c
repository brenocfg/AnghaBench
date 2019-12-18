#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_format; } ;
struct TYPE_9__ {TYPE_1__ audio; } ;
struct TYPE_12__ {TYPE_2__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_nb_blocks; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_frame_count; } ;
struct TYPE_13__ {TYPE_4__ eac3; TYPE_3__ truehd; int /*<<< orphan*/ * p_out_buf; } ;
typedef  TYPE_6__ filter_sys_t ;

/* Variables and functions */
#define  VLC_CODEC_EAC3 129 
#define  VLC_CODEC_TRUEHD 128 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Flush( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if( p_sys->p_out_buf != NULL )
    {
        block_Release( p_sys->p_out_buf );
        p_sys->p_out_buf = NULL;
    }
    switch( p_filter->fmt_in.audio.i_format )
    {
        case VLC_CODEC_TRUEHD:
            p_sys->truehd.i_frame_count = 0;
            break;
        case VLC_CODEC_EAC3:
            p_sys->eac3.i_nb_blocks = 0;
            break;
        default:
            break;
    }
}