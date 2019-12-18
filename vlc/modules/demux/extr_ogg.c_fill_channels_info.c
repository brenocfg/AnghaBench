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
typedef  int /*<<< orphan*/  pi_channels_map ;
struct TYPE_3__ {unsigned int i_channels; int i_physical_channels; } ;
typedef  TYPE_1__ audio_format_t ;

/* Variables and functions */
#define  AOUT_CHAN_CENTER 136 
#define  AOUT_CHAN_LEFT 135 
#define  AOUT_CHAN_LFE 134 
#define  AOUT_CHAN_MIDDLELEFT 133 
#define  AOUT_CHAN_MIDDLERIGHT 132 
#define  AOUT_CHAN_REARCENTER 131 
#define  AOUT_CHAN_REARLEFT 130 
#define  AOUT_CHAN_REARRIGHT 129 
#define  AOUT_CHAN_RIGHT 128 

__attribute__((used)) static void fill_channels_info(audio_format_t *audio)
{
    static const int pi_channels_map[9] =
    {
        0,
        AOUT_CHAN_CENTER,
        AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT,
        AOUT_CHAN_CENTER | AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT,
        AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_REARLEFT
            | AOUT_CHAN_REARRIGHT,
        AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER
            | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT,
        AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER
            | AOUT_CHAN_REARLEFT | AOUT_CHAN_REARRIGHT | AOUT_CHAN_LFE,
        AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER
            | AOUT_CHAN_REARCENTER | AOUT_CHAN_MIDDLELEFT
            | AOUT_CHAN_MIDDLERIGHT | AOUT_CHAN_LFE,
        AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT | AOUT_CHAN_CENTER | AOUT_CHAN_REARLEFT
            | AOUT_CHAN_REARRIGHT | AOUT_CHAN_MIDDLELEFT | AOUT_CHAN_MIDDLERIGHT
            | AOUT_CHAN_LFE,
    };

    unsigned chans = audio->i_channels;
    if (chans < sizeof(pi_channels_map) / sizeof(pi_channels_map[0]))
        audio->i_physical_channels = pi_channels_map[chans];
}