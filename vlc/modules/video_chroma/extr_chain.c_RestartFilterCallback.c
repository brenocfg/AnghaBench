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
typedef  char const* vlc_value_t ;
typedef  char const vlc_object_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  var_TriggerCallback (char const*,char*) ; 

__attribute__((used)) static int RestartFilterCallback( vlc_object_t *obj, char const *psz_name,
                                  vlc_value_t oldval, vlc_value_t newval,
                                  void *p_data )
{ VLC_UNUSED(obj); VLC_UNUSED(psz_name); VLC_UNUSED(oldval);
    VLC_UNUSED(newval);

    var_TriggerCallback( (vlc_object_t *)p_data, "video-filter" );
    return VLC_SUCCESS;
}