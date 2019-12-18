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
typedef  int /*<<< orphan*/  libvlc_video_format_cb ;
typedef  int /*<<< orphan*/  libvlc_video_cleanup_cb ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void libvlc_video_set_format_callbacks( libvlc_media_player_t *mp,
                                        libvlc_video_format_cb setup,
                                        libvlc_video_cleanup_cb cleanup )
{
    var_SetAddress( mp, "vmem-setup", setup );
    var_SetAddress( mp, "vmem-cleanup", cleanup );
}