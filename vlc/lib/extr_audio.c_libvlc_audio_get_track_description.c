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
typedef  int /*<<< orphan*/  libvlc_track_description_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/ * libvlc_get_track_description (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

libvlc_track_description_t *
        libvlc_audio_get_track_description( libvlc_media_player_t *p_mi )
{
    return libvlc_get_track_description( p_mi, AUDIO_ES );
}