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
 scalar_t__ isfinite (float) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_SetFloat (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

void libvlc_video_set_scale( libvlc_media_player_t *p_mp, float f_scale )
{
    if (isfinite(f_scale) && f_scale != 0.f)
        var_SetFloat (p_mp, "zoom", f_scale);
    var_SetBool (p_mp, "autoscale", f_scale == 0.f);

    /* Apply to current video outputs (if any) */
    size_t n;
    vout_thread_t **pp_vouts = GetVouts (p_mp, &n);
    for (size_t i = 0; i < n; i++)
    {
        vout_thread_t *p_vout = pp_vouts[i];

        if (isfinite(f_scale) && f_scale != 0.f)
            var_SetFloat (p_vout, "zoom", f_scale);
        var_SetBool (p_vout, "autoscale", f_scale == 0.f);
        vout_Release(p_vout);
    }
    free (pp_vouts);
}