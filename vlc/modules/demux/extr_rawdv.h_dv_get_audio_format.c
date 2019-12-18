#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int i_bitspersample; int i_channels; int i_rate; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_S16L ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dv_get_audio_format( es_format_t *p_fmt,
                                        const uint8_t *p_aaux_src )
{
    /* 12 bits non-linear will be converted to 16 bits linear */
    es_format_Init( p_fmt, AUDIO_ES, VLC_CODEC_S16L );

    p_fmt->audio.i_bitspersample = 16;
    p_fmt->audio.i_channels = 2;
    switch( (p_aaux_src[4-1] >> 3) & 0x07 )
    {
    case 0:
        p_fmt->audio.i_rate = 48000;
        break;
    case 1:
        p_fmt->audio.i_rate = 44100;
        break;
    case 2:
    default:
        p_fmt->audio.i_rate = 32000;
        break;
    }
}