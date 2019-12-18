#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 

void AudioPostrenderDefaultCallback( void* p_audio_data, uint8_t* p_pcm_buffer, unsigned int channels,
                                     unsigned int rate, unsigned int nb_samples, unsigned int bits_per_sample,
                                     size_t size, vlc_tick_t pts )
{
    VLC_UNUSED( p_audio_data ); VLC_UNUSED( p_pcm_buffer );
    VLC_UNUSED( channels ); VLC_UNUSED( rate ); VLC_UNUSED( nb_samples );
    VLC_UNUSED( bits_per_sample ); VLC_UNUSED( size ); VLC_UNUSED( pts );
}