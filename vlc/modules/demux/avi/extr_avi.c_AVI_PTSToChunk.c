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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_scale; } ;
typedef  TYPE_1__ avi_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_Rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t AVI_PTSToChunk( avi_track_t *tk, vlc_tick_t i_pts )
{
    if( !tk->i_scale )
        return 0;

    i_pts = AVI_Rescale( i_pts, tk->i_scale, tk->i_rate );
    return SEC_FROM_VLC_TICK(i_pts);
}