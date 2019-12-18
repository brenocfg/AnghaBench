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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  fe_sec_tone_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_TONE_OFF ; 
 int /*<<< orphan*/  SEC_TONE_ON ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static fe_sec_tone_mode_t DecodeTone( vlc_object_t *p_access )
{
    switch( var_GetInteger( p_access, "dvb-tone" ) )
    {
        case 0:  return SEC_TONE_OFF;
        case 1:  return SEC_TONE_ON;
        default: return SEC_TONE_OFF;
    }
}