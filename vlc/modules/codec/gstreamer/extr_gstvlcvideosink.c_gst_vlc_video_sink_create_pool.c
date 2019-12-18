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
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gint ;
struct TYPE_3__ {int /*<<< orphan*/  p_dec; int /*<<< orphan*/  p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoSink ;
typedef  int /*<<< orphan*/  GstVlcVideoPool ;
typedef  int /*<<< orphan*/  GstStructure ;
typedef  int /*<<< orphan*/  GstCaps ;

/* Variables and functions */
 int /*<<< orphan*/  GST_BUFFER_POOL_CAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_buffer_pool_config_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gst_buffer_pool_get_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_buffer_pool_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gst_vlc_video_pool_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GstVlcVideoPool* gst_vlc_video_sink_create_pool(
        GstVlcVideoSink *p_vsink, GstCaps *p_caps, gsize i_size, gint i_min )
{
    GstVlcVideoPool *p_pool;
    GstStructure *p_config;

    p_pool = gst_vlc_video_pool_new( p_vsink->p_allocator, p_vsink->p_dec );

    p_config = gst_buffer_pool_get_config( GST_BUFFER_POOL_CAST( p_pool ));
    gst_buffer_pool_config_set_params( p_config, p_caps, i_size, i_min, 0);

    if( !gst_buffer_pool_set_config( GST_BUFFER_POOL_CAST( p_pool ), p_config ))
        goto config_failed;

    return p_pool;

config_failed:
    {
        gst_object_unref (p_pool);
        return NULL;
    }
}