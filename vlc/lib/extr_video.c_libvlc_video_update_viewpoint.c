#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fov; int /*<<< orphan*/  roll; int /*<<< orphan*/  pitch; int /*<<< orphan*/  yaw; } ;
typedef  TYPE_1__ vlc_viewpoint_t ;
struct TYPE_8__ {int /*<<< orphan*/  f_field_of_view; int /*<<< orphan*/  f_roll; int /*<<< orphan*/  f_pitch; int /*<<< orphan*/  f_yaw; } ;
typedef  TYPE_2__ libvlc_video_viewpoint_t ;
struct TYPE_9__ {int /*<<< orphan*/  player; } ;
typedef  TYPE_3__ libvlc_media_player_t ;
typedef  enum vlc_player_whence { ____Placeholder_vlc_player_whence } vlc_player_whence ;

/* Variables and functions */
 int VLC_PLAYER_WHENCE_ABSOLUTE ; 
 int VLC_PLAYER_WHENCE_RELATIVE ; 
 int /*<<< orphan*/  vlc_player_UpdateViewpoint (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

int libvlc_video_update_viewpoint( libvlc_media_player_t *p_mi,
                                   const libvlc_video_viewpoint_t *p_viewpoint,
                                   bool b_absolute )
{
    vlc_viewpoint_t update = {
        .yaw   = p_viewpoint->f_yaw,
        .pitch = p_viewpoint->f_pitch,
        .roll  = p_viewpoint->f_roll,
        .fov   = p_viewpoint->f_field_of_view,
    };

    enum vlc_player_whence whence = b_absolute ? VLC_PLAYER_WHENCE_ABSOLUTE
                                               : VLC_PLAYER_WHENCE_RELATIVE;
    vlc_player_UpdateViewpoint(p_mi->player, &update, whence);

    /* may not fail anymore, keep int not to break the API */
    return 0;
}