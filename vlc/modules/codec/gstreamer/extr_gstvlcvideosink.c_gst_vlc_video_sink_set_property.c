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
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_3__ {int /*<<< orphan*/  b_use_pool; int /*<<< orphan*/ * p_dec; int /*<<< orphan*/  p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoSink ;
typedef  int /*<<< orphan*/  GstAllocator ;
typedef  int /*<<< orphan*/  GValue ;
typedef  int /*<<< orphan*/  GParamSpec ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/  GST_IS_VLC_PICTURE_PLANE_ALLOCATOR (int /*<<< orphan*/ *) ; 
 TYPE_1__* GST_VLC_VIDEO_SINK (int /*<<< orphan*/ *) ; 
#define  PROP_ALLOCATOR 130 
#define  PROP_ID 129 
#define  PROP_USE_POOL 128 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_get_boolean (int /*<<< orphan*/  const*) ; 
 scalar_t__ g_value_get_pointer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gst_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_object_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void gst_vlc_video_sink_set_property( GObject *p_object, guint i_prop_id,
        const GValue *p_value, GParamSpec *p_pspec )
{
    VLC_UNUSED( p_pspec );

    GstVlcVideoSink *p_vsink = GST_VLC_VIDEO_SINK( p_object );

    switch( i_prop_id )
    {
        case PROP_ALLOCATOR:
        {
            GstAllocator *p_allocator = (GstAllocator*) g_value_get_pointer(
                    p_value );
            if( GST_IS_VLC_PICTURE_PLANE_ALLOCATOR( p_allocator ))
            {
                if( p_vsink->p_allocator )
                    gst_object_unref( p_vsink->p_allocator );
                p_vsink->p_allocator = gst_object_ref( p_allocator );
            } else
                msg_Err( p_vsink->p_dec, "Invalid Allocator set");
        }
        break;

        case PROP_ID:
        {
            p_vsink->p_dec = (decoder_t*) g_value_get_pointer( p_value );
        }
        break;

        case PROP_USE_POOL:
        {
            p_vsink->b_use_pool = g_value_get_boolean( p_value );
        }
        break;

        default:
        break;
    }
}