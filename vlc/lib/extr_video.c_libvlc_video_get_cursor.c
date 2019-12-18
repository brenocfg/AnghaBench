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
 int /*<<< orphan*/ * GetVout (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  var_GetCoords (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

int libvlc_video_get_cursor( libvlc_media_player_t *mp, unsigned num,
                             int *restrict px, int *restrict py )
{
    vout_thread_t *p_vout = GetVout (mp, num);
    if (p_vout == NULL)
        return -1;

    var_GetCoords (p_vout, "mouse-moved", px, py);
    vout_Release(p_vout);
    return 0;
}