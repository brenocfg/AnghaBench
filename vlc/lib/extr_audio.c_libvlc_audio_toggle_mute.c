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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int libvlc_audio_get_mute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_audio_set_mute (int /*<<< orphan*/ *,int) ; 

void libvlc_audio_toggle_mute( libvlc_media_player_t *mp )
{
    int mute = libvlc_audio_get_mute( mp );
    if( mute != -1 )
        libvlc_audio_set_mute( mp, !mute );
}