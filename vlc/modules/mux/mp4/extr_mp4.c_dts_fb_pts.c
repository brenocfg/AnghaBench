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
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 

__attribute__((used)) static inline vlc_tick_t dts_fb_pts( const block_t *p_data )
{
    return p_data->i_dts != VLC_TICK_INVALID ? p_data->i_dts: p_data->i_pts;
}