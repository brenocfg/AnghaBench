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
typedef  void* libvlc_video_swap_cb ;
typedef  void* libvlc_video_direct3d_update_output_cb ;
typedef  void* libvlc_video_direct3d_start_end_rendering_cb ;
typedef  void* libvlc_video_direct3d_set_resize_cb ;
typedef  void* libvlc_video_direct3d_select_plane_cb ;
typedef  scalar_t__ libvlc_video_direct3d_engine_t ;
typedef  void* libvlc_video_direct3d_device_setup_cb ;
typedef  void* libvlc_video_direct3d_device_cleanup_cb ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 scalar_t__ libvlc_video_direct3d_engine_d3d11 ; 
 scalar_t__ libvlc_video_direct3d_engine_d3d9 ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

bool libvlc_video_direct3d_set_callbacks(libvlc_media_player_t *mp,
                                         libvlc_video_direct3d_engine_t engine,
                                         libvlc_video_direct3d_device_setup_cb setup_cb,
                                         libvlc_video_direct3d_device_cleanup_cb cleanup_cb,
                                         libvlc_video_direct3d_set_resize_cb resize_cb,
                                         libvlc_video_direct3d_update_output_cb update_output_cb,
                                         libvlc_video_swap_cb swap_cb,
                                         libvlc_video_direct3d_start_end_rendering_cb makeCurrent_cb,
                                         libvlc_video_direct3d_select_plane_cb select_plane_cb,
                                         void *opaque)
{
    var_SetString( mp, "window", "wextern");

    if ( engine == libvlc_video_direct3d_engine_d3d11 )
    {
        var_SetString ( mp, "vout", "direct3d11" );
        var_SetString ( mp, "dec-dev", "d3d11-device" );
    }
    else if ( engine == libvlc_video_direct3d_engine_d3d9 )
    {
        var_SetString ( mp, "vout", "direct3d9" );
        var_SetString ( mp, "dec-dev", "d3d9-device" );
    }
    else
        return false;

    var_SetAddress( mp, "vout-cb-opaque", opaque );
    var_SetAddress( mp, "vout-cb-setup", setup_cb );
    var_SetAddress( mp, "vout-cb-cleanup", cleanup_cb );
    var_SetAddress( mp, "vout-cb-resize-cb", resize_cb );
    var_SetAddress( mp, "vout-cb-update-output", update_output_cb );
    var_SetAddress( mp, "vout-cb-swap", swap_cb );
    var_SetAddress( mp, "vout-cb-make-current", makeCurrent_cb );
    var_SetAddress( mp, "vout-cb-select-plane", select_plane_cb );
    return true;
}