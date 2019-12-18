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
struct TYPE_3__ {int /*<<< orphan*/  video_filter; int /*<<< orphan*/  deinterlace; int /*<<< orphan*/  crop; int /*<<< orphan*/  aspect_ratio; } ;
typedef  TYPE_1__ vlc_ml_playback_states_all ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void vlc_ml_playback_states_all_release( vlc_ml_playback_states_all* prefs )
{
    free( prefs->aspect_ratio );
    free( prefs->crop );
    free( prefs->deinterlace );
    free( prefs->video_filter );
}