#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ encoder_t ;
struct TYPE_8__ {TYPE_1__* pts_tlb; } ;
typedef  TYPE_3__ encoder_sys_t ;
struct TYPE_6__ {int b_empty; scalar_t__ u_pnum; int /*<<< orphan*/  i_pts; } ;

/* Variables and functions */
 int SCHRO_PTS_TLB_SIZE ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,scalar_t__) ; 

__attribute__((used)) static vlc_tick_t GetPicturePTS( encoder_t *p_enc, uint32_t u_pnum )
{
    encoder_sys_t *p_sys = p_enc->p_sys;

    for( int i = 0; i < SCHRO_PTS_TLB_SIZE; i++ )
    {
        if( !p_sys->pts_tlb[i].b_empty &&
            p_sys->pts_tlb[i].u_pnum == u_pnum )
        {
             p_sys->pts_tlb[i].b_empty = true;
             return p_sys->pts_tlb[i].i_pts;
        }
    }

    msg_Err( p_enc, "Could not retrieve PTS for picture %u", u_pnum );
    return VLC_TICK_INVALID;
}