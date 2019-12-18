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
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 

void libvlc_audio_set_format( libvlc_media_player_t *mp, const char *format,
                              unsigned rate, unsigned channels )
{
    var_SetString( mp, "amem-format", format );
    var_SetInteger( mp, "amem-rate", rate );
    var_SetInteger( mp, "amem-channels", channels );
}