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
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetAOut (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 

int libvlc_audio_get_channel( libvlc_media_player_t *mp )
{
    audio_output_t *p_aout = GetAOut( mp );
    if( !p_aout )
        return 0;

    int val = var_GetInteger( p_aout, "stereo-mode" );
    aout_Release(p_aout);
    return val;
}