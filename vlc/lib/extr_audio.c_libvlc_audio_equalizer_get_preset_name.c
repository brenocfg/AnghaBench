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

/* Variables and functions */
 unsigned int NB_PRESETS ; 
 char const** preset_list_text ; 

const char *libvlc_audio_equalizer_get_preset_name( unsigned u_index )
{
    if ( u_index >= NB_PRESETS )
        return NULL;

    return preset_list_text[ u_index ];
}