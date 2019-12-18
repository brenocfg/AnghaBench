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
typedef  int vlc_tick_t ;
typedef  int int64_t ;
struct TYPE_3__ {int i_samplesize; int /*<<< orphan*/  i_scale; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_1__ avi_track_t ;

/* Variables and functions */
 int AVI_Rescale (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CLOCK_FREQ ; 

__attribute__((used)) static vlc_tick_t AVI_GetDPTS( avi_track_t *tk, int64_t i_count )
{
    vlc_tick_t i_dpts = 0;

    if( !tk->i_rate )
        return 0;

    if( !tk->i_scale )
        return 0;

    i_dpts = AVI_Rescale( CLOCK_FREQ * i_count, tk->i_rate, tk->i_scale );

    if( tk->i_samplesize )
    {
        return i_dpts / tk->i_samplesize;
    }
    return i_dpts;
}