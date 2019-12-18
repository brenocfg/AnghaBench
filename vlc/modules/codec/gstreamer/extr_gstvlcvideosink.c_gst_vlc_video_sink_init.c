#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  b_use_pool; } ;
typedef  TYPE_1__ GstVlcVideoSink ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GST_BASE_SINK (TYPE_1__*) ; 
 int /*<<< orphan*/  gst_base_sink_set_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gst_vlc_video_sink_init( GstVlcVideoSink *p_vlc_video_sink )
{
    p_vlc_video_sink->b_use_pool = FALSE;
    gst_base_sink_set_sync( GST_BASE_SINK( p_vlc_video_sink), FALSE );
}