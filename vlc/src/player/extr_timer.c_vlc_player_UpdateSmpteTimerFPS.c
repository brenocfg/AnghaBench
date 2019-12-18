#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_2__ {unsigned int frame_rate; unsigned int frame_rate_base; int df; int df_fps; int frames_per_10mins; scalar_t__ frame_resolution; } ;
struct vlc_player_timer_source {TYPE_1__ smpte; } ;

/* Variables and functions */

__attribute__((used)) static void
vlc_player_UpdateSmpteTimerFPS(vlc_player_t *player,
                               struct vlc_player_timer_source *source,
                               unsigned frame_rate, unsigned frame_rate_base)
{
    (void) player;
    source->smpte.frame_rate = frame_rate;
    source->smpte.frame_rate_base = frame_rate_base;

    /* Calculate everything that will be needed to create smpte timecodes */
    source->smpte.frame_resolution = 0;

    unsigned max_frames = frame_rate / frame_rate_base;

    if (max_frames == 29 && (100 * frame_rate / frame_rate_base) == 2997)
    {
        /* SMPTE Timecode: 29.97 fps DF */
        source->smpte.df = 2;
        source->smpte.df_fps = 30;
        source->smpte.frames_per_10mins = 17982; /* 29.97 * 60 * 10 */
    }
    else if (max_frames == 59 && (100 * frame_rate / frame_rate_base) == 5994)
    {
        /* SMPTE Timecode: 59.94 fps DF */
        source->smpte.df = 4;
        source->smpte.df_fps = 60;
        source->smpte.frames_per_10mins = 35964; /* 59.94 * 60 * 10 */
    }
    else
        source->smpte.df = 0;

    while (max_frames != 0)
    {
        max_frames /= 10;
        source->smpte.frame_resolution++;
    }
}