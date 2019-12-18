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
struct TYPE_3__ {int i_use_flags; } ;
typedef  TYPE_1__ mp4_track_t ;

/* Variables and functions */
 int USEAS_CHAPTERS ; 
 int USEAS_TIMECODE ; 

__attribute__((used)) static bool MP4_isMetadata( const mp4_track_t *tk )
{
    return tk->i_use_flags & (USEAS_CHAPTERS|USEAS_TIMECODE);
}