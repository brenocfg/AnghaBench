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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 

void AudioPrerenderDefaultCallback( void* p_audio_data, uint8_t** pp_pcm_buffer, size_t size )
{
    VLC_UNUSED( p_audio_data ); VLC_UNUSED( pp_pcm_buffer ); VLC_UNUSED( size );
}