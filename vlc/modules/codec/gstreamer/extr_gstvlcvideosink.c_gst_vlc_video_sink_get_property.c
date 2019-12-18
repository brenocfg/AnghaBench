#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int guint ;
struct TYPE_3__ {int /*<<< orphan*/  b_use_pool; int /*<<< orphan*/  p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoSink ;
typedef  int /*<<< orphan*/  GValue ;
typedef  int /*<<< orphan*/  GParamSpec ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 TYPE_1__* GST_VLC_VIDEO_SINK (int /*<<< orphan*/ *) ; 
#define  PROP_ALLOCATOR 129 
#define  PROP_USE_POOL 128 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_set_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_value_set_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gst_vlc_video_sink_get_property( GObject *p_object, guint i_prop_id,
    GValue *p_value, GParamSpec *p_pspec )
{
    VLC_UNUSED( p_pspec );

    GstVlcVideoSink *p_vsink = GST_VLC_VIDEO_SINK( p_object );

    switch( i_prop_id )
    {
        case PROP_ALLOCATOR:
            g_value_set_pointer( p_value, p_vsink->p_allocator );
        break;

        case PROP_USE_POOL:
            g_value_set_boolean( p_value, p_vsink->b_use_pool );
        break;

        default:
        break;
   }
}