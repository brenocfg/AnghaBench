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
typedef  void* vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  VoutSaveSnapshot (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SnapshotCallback( vlc_object_t *p_this, char const *psz_cmd,
                       vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    vout_thread_t *p_vout = (vout_thread_t *)p_this;
    VLC_UNUSED(psz_cmd); VLC_UNUSED(oldval);
    VLC_UNUSED(newval); VLC_UNUSED(p_data);

    VoutSaveSnapshot( p_vout );
    return VLC_SUCCESS;
}