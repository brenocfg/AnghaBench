#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_3__ {int i_flags; scalar_t__ i_buffer; scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int BLOCK_FLAG_PREROLL ; 
 int /*<<< orphan*/  PREROLL_FORCED ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  __MIN (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void DecoderUpdatePreroll( vlc_tick_t *pi_preroll, const block_t *p )
{
    if( p->i_flags & BLOCK_FLAG_PREROLL )
        *pi_preroll = PREROLL_FORCED;
    /* Check if we can use the packet for end of preroll */
    else if( (p->i_flags & BLOCK_FLAG_DISCONTINUITY) &&
             (p->i_buffer == 0 || (p->i_flags & BLOCK_FLAG_CORRUPTED)) )
        *pi_preroll = PREROLL_FORCED;
    else if( p->i_dts != VLC_TICK_INVALID )
        *pi_preroll = __MIN( *pi_preroll, p->i_dts );
    else if( p->i_pts != VLC_TICK_INVALID )
        *pi_preroll = __MIN( *pi_preroll, p->i_pts );
}