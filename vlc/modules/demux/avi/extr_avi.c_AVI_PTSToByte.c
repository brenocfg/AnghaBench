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
struct TYPE_3__ {int i_samplesize; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_scale; } ;
typedef  TYPE_1__ avi_track_t ;

/* Variables and functions */
 int AVI_Rescale (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CLOCK_FREQ ; 

__attribute__((used)) static int64_t AVI_PTSToByte( avi_track_t *tk, vlc_tick_t i_pts )
{
    if( !tk->i_scale || !tk->i_samplesize )
        return 0;

    i_pts = AVI_Rescale( i_pts, tk->i_scale, tk->i_rate );
    return i_pts / CLOCK_FREQ * tk->i_samplesize;
}