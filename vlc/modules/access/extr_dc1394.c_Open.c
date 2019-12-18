#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_14__ {int i_width; int i_height; } ;
struct TYPE_15__ {TYPE_1__ video; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_16__ {int /*<<< orphan*/ * out; int /*<<< orphan*/  psz_location; TYPE_4__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_17__ {int width; int height; int brightness; int focus; int selected_camera; int dma_buffers; int /*<<< orphan*/ * camera; int /*<<< orphan*/  p_es_video; int /*<<< orphan*/  video_mode; int /*<<< orphan*/  frame_rate; scalar_t__ video_device; int /*<<< orphan*/  features; scalar_t__ reset_bus; int /*<<< orphan*/ * p_dccontext; } ;
typedef  TYPE_4__ demux_sys_t ;
typedef  scalar_t__ dc1394error_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  DC1394_CAPTURE_FLAGS_DEFAULT ; 
 int /*<<< orphan*/  DC1394_FEATURE_FOCUS ; 
 int /*<<< orphan*/  DC1394_FRAMERATE_15 ; 
 int /*<<< orphan*/  DC1394_ISO_SPEED_400 ; 
 scalar_t__ DC1394_NO_BANDWIDTH ; 
 int /*<<< orphan*/  DC1394_ON ; 
 scalar_t__ DC1394_SUCCESS ; 
 int /*<<< orphan*/  DC1394_VIDEO_MODE_640x480_YUV422 ; 
 int /*<<< orphan*/  Demux ; 
 scalar_t__ FindCamera (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_UYVY ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ dc1394_camera_print_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dc1394_camera_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ dc1394_capture_set_device_filename (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ dc1394_capture_setup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc1394_capture_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ dc1394_feature_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc1394_feature_print_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dc1394_feature_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dc1394_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dc1394_new () ; 
 scalar_t__ dc1394_reset_bus (int /*<<< orphan*/ *) ; 
 scalar_t__ dc1394_video_set_framerate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dc1394_video_set_iso_speed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dc1394_video_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dc1394_video_set_transmission (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,...) ; 
 scalar_t__ process_options (TYPE_3__*) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_4__* vlc_obj_calloc (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    demux_t      *p_demux = (demux_t*)p_this;
    demux_sys_t  *p_sys;
    es_format_t   fmt;
    dc1394error_t res;

    if (p_demux->out == NULL)
        return VLC_EGENERIC;

    /* Set up p_demux */
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;

    p_demux->p_sys = p_sys = vlc_obj_calloc( p_this, 1, sizeof( demux_sys_t ) );
    if( !p_sys )
        return VLC_ENOMEM;

    memset( &fmt, 0, sizeof( es_format_t ) );

    /* DEFAULTS */
    p_sys->video_mode      = DC1394_VIDEO_MODE_640x480_YUV422;
    p_sys->width           = 640;
    p_sys->height          = 480;
    p_sys->frame_rate      = DC1394_FRAMERATE_15;
    p_sys->brightness      = 200;
    p_sys->focus           = 0;
    p_sys->p_dccontext     = NULL;
    p_sys->camera          = NULL;
    p_sys->selected_camera = -1;
    p_sys->dma_buffers     = 1;
    p_sys->reset_bus       = 0;

    /* PROCESS INPUT OPTIONS */
    if( process_options(p_demux) != VLC_SUCCESS )
    {
        msg_Err( p_demux, "Bad MRL, please check the option line "
                          "(MRL was: %s)",
                          p_demux->psz_location );
        return VLC_EGENERIC;
    }

    p_sys->p_dccontext = dc1394_new();
    if( !p_sys->p_dccontext )
    {
        msg_Err( p_demux, "Failed to initialise libdc1394");
        return VLC_EGENERIC;
    }

    if( FindCamera( p_sys, p_demux ) != VLC_SUCCESS )
    {
        dc1394_free( p_sys->p_dccontext );
        return VLC_EGENERIC;
    }

    if( !p_sys->camera )
    {
        msg_Err( p_demux, "No camera found !!" );
        dc1394_free( p_sys->p_dccontext );
        return VLC_EGENERIC;
    }

    if( p_sys->reset_bus )
    {
        if( dc1394_reset_bus( p_sys->camera ) != DC1394_SUCCESS )
        {
            msg_Err( p_demux, "Unable to reset IEEE 1394 bus");
            Close( p_this );
            return VLC_EGENERIC;
        }
        else msg_Dbg( p_demux, "Successfully reset IEEE 1394 bus");
    }

    if( dc1394_camera_reset( p_sys->camera ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to reset camera");
        Close( p_this );
        return VLC_EGENERIC;
    }

    if( dc1394_camera_print_info( p_sys->camera,
                  stderr ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to print camera info");
        Close( p_this );
        return VLC_EGENERIC;
    }

    if( dc1394_feature_get_all( p_sys->camera,
                &p_sys->features ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to get feature set");
        Close( p_this );
        return VLC_EGENERIC;
    }
    // TODO: only print features if verbosity increased
    dc1394_feature_print_all(&p_sys->features, stderr);

#if 0 //"Note that you need to execute this function only if you use exotic video1394 device names. /dev/video1394, /dev/video1394/* and /dev/video1394-* are automatically recognized." http://damien.douxchamps.net/ieee1394/libdc1394/v2.x/api/capture/
    if( p_sys->video_device )
    {
        if( dc1394_capture_set_device_filename( p_sys->camera,
                        p_sys->video_device ) != DC1394_SUCCESS )
        {
            msg_Err( p_demux, "Unable to set video device");
            Close( p_this );
            return VLC_EGENERIC;
        }
    }
#endif

    if( p_sys->focus )
    {
        if( dc1394_feature_set_value( p_sys->camera,
                      DC1394_FEATURE_FOCUS,
                      p_sys->focus ) != DC1394_SUCCESS )
        {
            msg_Err( p_demux, "Unable to set initial focus to %u",
                     p_sys->focus );
        }
        else
            msg_Dbg( p_demux, "Initial focus set to %u", p_sys->focus );
    }

    if( dc1394_feature_set_value( p_sys->camera,
                  DC1394_FEATURE_FOCUS,
                  p_sys->brightness ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to set initial brightness to %u",
                 p_sys->brightness );
    }
    else
        msg_Dbg( p_demux, "Initial brightness set to %u", p_sys->brightness );

    if( dc1394_video_set_framerate( p_sys->camera,
                    p_sys->frame_rate ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to set framerate");
        Close( p_this );
        return VLC_EGENERIC;
    }

    if( dc1394_video_set_mode( p_sys->camera,
                   p_sys->video_mode ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to set video mode");
        Close( p_this );
        return VLC_EGENERIC;
    }

    if( dc1394_video_set_iso_speed( p_sys->camera,
                    DC1394_ISO_SPEED_400 ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to set iso speed");
        Close( p_this );
        return VLC_EGENERIC;
    }

    /* and setup capture */
    res = dc1394_capture_setup( p_sys->camera,
                    p_sys->dma_buffers,
                DC1394_CAPTURE_FLAGS_DEFAULT);
    if( res != DC1394_SUCCESS )
    {
        if( res == DC1394_NO_BANDWIDTH )
        {
            msg_Err( p_demux ,"No bandwidth: try adding the "
             "\"resetbus\" option" );
        }
        else
        {
            msg_Err( p_demux ,"Unable to setup capture" );
        }
        Close( p_this );
        return VLC_EGENERIC;
    }

    /* TODO - UYV444 chroma converter is missing, when it will be available
     * fourcc will become variable (and not just a fixed value for UYVY)
     */
    es_format_Init( &fmt, VIDEO_ES, VLC_CODEC_UYVY );

    fmt.video.i_width = p_sys->width;
    fmt.video.i_height = p_sys->height;

    msg_Dbg( p_demux, "Added new video es %4.4s %dx%d",
             (char*)&fmt.i_codec, fmt.video.i_width, fmt.video.i_height );

    p_sys->p_es_video = es_out_Add( p_demux->out, &fmt );

    /* have the camera start sending us data */
    if( dc1394_video_set_transmission( p_sys->camera,
                       DC1394_ON ) != DC1394_SUCCESS )
    {
        msg_Err( p_demux, "Unable to start camera iso transmission" );
        dc1394_capture_stop( p_sys->camera );
        Close( p_this );
        return VLC_EGENERIC;
    }
    msg_Dbg( p_demux, "Set iso transmission" );
    // TODO: reread camera
    return VLC_SUCCESS;
}