#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int i_tracks; TYPE_2__* track; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_5__ {scalar_t__ i_cat; } ;
struct TYPE_6__ {int /*<<< orphan*/  b_selected; TYPE_1__ fmt; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ VIDEO_ES ; 

__attribute__((used)) static unsigned GetSeekTrackIndex( demux_sys_t *p_sys )
{
    unsigned cand = 0;
    for( unsigned i=0; i<p_sys->i_tracks; i++ )
    {
        if( p_sys->track[i].fmt.i_cat == VIDEO_ES ||
            p_sys->track[i].fmt.i_cat == AUDIO_ES )
        {
            if( cand != i && !p_sys->track[cand].b_selected )
                cand = i;
        }
    }
    return cand;
}