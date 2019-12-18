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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  char const* vlc_value_t ;
typedef  char const vlc_object_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  vout_ControlChangeSubFilters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int RestartSubFilterCallback(vlc_object_t *obj, char const *psz_var,
                                    vlc_value_t oldval, vlc_value_t newval,
                                    void *p_data)
{ VLC_UNUSED(obj); VLC_UNUSED(psz_var); VLC_UNUSED(oldval); VLC_UNUSED(newval);
    vout_ControlChangeSubFilters((vout_thread_t *)p_data, NULL);
    return VLC_SUCCESS;
}