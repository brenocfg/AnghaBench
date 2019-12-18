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
 char* aout_DeviceGet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 

char *libvlc_audio_output_device_get( libvlc_media_player_t *mp )
{
    audio_output_t *aout = GetAOut( mp );
    if( aout == NULL )
        return NULL;

    char *devid = aout_DeviceGet( aout );

    aout_Release(aout);

    return devid;
}