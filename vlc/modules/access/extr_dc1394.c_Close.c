#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {int /*<<< orphan*/  video_device; int /*<<< orphan*/  p_dccontext; int /*<<< orphan*/  camera; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DC1394_OFF ; 
 scalar_t__ DC1394_SUCCESS ; 
 int /*<<< orphan*/  dc1394_camera_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc1394_capture_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc1394_free (int /*<<< orphan*/ ) ; 
 scalar_t__ dc1394_video_set_transmission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    /* Stop data transmission */
    if( dc1394_video_set_transmission( p_sys->camera,
                       DC1394_OFF ) != DC1394_SUCCESS )
        msg_Err( p_demux, "Unable to stop camera iso transmission" );

    /* Close camera */
    dc1394_capture_stop( p_sys->camera );

    dc1394_camera_free(p_sys->camera);
    dc1394_free(p_sys->p_dccontext);

    free( p_sys->video_device );
}