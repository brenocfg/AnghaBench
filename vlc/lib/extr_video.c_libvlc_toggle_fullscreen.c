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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** GetVouts (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,char*,int) ; 
 int var_ToggleBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

void libvlc_toggle_fullscreen( libvlc_media_player_t *p_mi )
{
    bool b_fullscreen = var_ToggleBool (p_mi, "fullscreen");

    /* Apply to current video outputs (if any) */
    size_t n;
    vout_thread_t **pp_vouts = GetVouts (p_mi, &n);
    for (size_t i = 0; i < n; i++)
    {
        vout_thread_t *p_vout = pp_vouts[i];

        var_SetBool (p_vout, "fullscreen", b_fullscreen);
        vout_Release(p_vout);
    }
    free (pp_vouts);
}