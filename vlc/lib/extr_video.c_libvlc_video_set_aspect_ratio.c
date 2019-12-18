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
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

void libvlc_video_set_aspect_ratio( libvlc_media_player_t *p_mi,
                                    const char *psz_aspect )
{
    if (psz_aspect == NULL)
        psz_aspect = "";
    var_SetString (p_mi, "aspect-ratio", psz_aspect);

    size_t n;
    vout_thread_t **pp_vouts = GetVouts (p_mi, &n);
    for (size_t i = 0; i < n; i++)
    {
        vout_thread_t *p_vout = pp_vouts[i];

        var_SetString (p_vout, "aspect-ratio", psz_aspect);
        vout_Release(p_vout);
    }
    free (pp_vouts);
}