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
typedef  void* libvlc_video_update_output_cb ;
typedef  void* libvlc_video_swap_cb ;
typedef  void* libvlc_video_setup_cb ;
typedef  void* libvlc_video_makeCurrent_cb ;
typedef  void* libvlc_video_getProcAddress_cb ;
typedef  scalar_t__ libvlc_video_engine_t ;
typedef  void* libvlc_video_cleanup_cb ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 scalar_t__ libvlc_video_engine_gles2 ; 
 scalar_t__ libvlc_video_engine_opengl ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

bool libvlc_video_set_output_callbacks(libvlc_media_player_t *mp,
                                       libvlc_video_engine_t engine,
                                       libvlc_video_setup_cb setup_cb,
                                       libvlc_video_cleanup_cb cleanup_cb,
                                       libvlc_video_update_output_cb update_output_cb,
                                       libvlc_video_swap_cb swap_cb,
                                       libvlc_video_makeCurrent_cb makeCurrent_cb,
                                       libvlc_video_getProcAddress_cb getProcAddress_cb,
                                       void *opaque)
{
#ifdef __ANDROID__
    //use the default android window
    var_SetString( mp, "window", "");
#else
    var_SetString( mp, "window", "wdummy");
#endif

    if( engine == libvlc_video_engine_gles2 )
    {
        var_SetString ( mp, "vout", "gles2" );
        var_SetString ( mp, "gles2", "vgl" );
    }
    else if( engine == libvlc_video_engine_opengl )
    {
        var_SetString ( mp, "vout", "gl" );
        var_SetString ( mp, "gl", "vgl");
    }
    else
        return false;

    var_SetAddress( mp, "vout-cb-opaque", opaque );
    var_SetAddress( mp, "vout-cb-setup", setup_cb );
    var_SetAddress( mp, "vout-cb-cleanup", cleanup_cb );
    var_SetAddress( mp, "vout-cb-update-output", update_output_cb );
    var_SetAddress( mp, "vout-cb-swap", swap_cb );
    var_SetAddress( mp, "vout-cb-get-proc-address", getProcAddress_cb );
    var_SetAddress( mp, "vout-cb-make-current", makeCurrent_cb );
    return true;
}