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

__attribute__((used)) static void libvlc_video_set_crop(libvlc_media_player_t *mp,
                                  const char *geometry)
{
    var_SetString(mp, "crop", geometry);

    size_t n;
    vout_thread_t **vouts = GetVouts(mp, &n);

    for (size_t i = 0; i < n; i++)
    {
        var_SetString(vouts[i], "crop", geometry);
        vout_Release(vouts[i]);
    }
    free(vouts);
}