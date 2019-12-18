#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
typedef  scalar_t__ gboolean ;
struct TYPE_9__ {int /*<<< orphan*/  info; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_dec; scalar_t__ b_use_pool; } ;
typedef  TYPE_1__ GstVlcVideoSink ;
typedef  TYPE_2__ GstVideoInfo ;
typedef  int /*<<< orphan*/  GstQuery ;
typedef  int /*<<< orphan*/  GstCaps ;
typedef  int /*<<< orphan*/  GstBufferPool ;
typedef  int /*<<< orphan*/  GstBaseSink ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GST_VIDEO_INFO_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GST_VIDEO_META_API_TYPE ; 
 TYPE_6__* GST_VLC_VIDEO_POOL_CAST (int /*<<< orphan*/ *) ; 
 TYPE_1__* GST_VLC_VIDEO_SINK (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  gst_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_query_add_allocation_meta (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_query_add_allocation_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_query_parse_allocation (int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  gst_video_info_from_caps (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gst_vlc_video_sink_create_pool (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static gboolean gst_vlc_video_sink_propose_allocation( GstBaseSink* p_bsink,
        GstQuery* p_query )
{
    GstVlcVideoSink *p_vsink = GST_VLC_VIDEO_SINK( p_bsink );
    GstCaps *p_caps;
    gboolean b_need_pool;
    GstBufferPool* p_pool = NULL;
    gsize i_size;

    gst_query_parse_allocation (p_query, &p_caps, &b_need_pool);
    if( p_caps == NULL )
        goto no_caps;

    if( p_vsink->b_use_pool && b_need_pool )
    {
        GstVideoInfo info;

        if( !gst_video_info_from_caps( &info, p_caps ))
            goto invalid_caps;

        p_pool = (GstBufferPool*) gst_vlc_video_sink_create_pool( p_vsink,
                p_caps, info.size, 2 );
        if( p_pool == NULL )
            goto no_pool;

        i_size = GST_VIDEO_INFO_SIZE( &GST_VLC_VIDEO_POOL_CAST( p_pool )->info);
    }

    if( p_pool )
    {
        /* we need at least 2 buffer because we hold on to the last one */
        gst_query_add_allocation_pool( p_query, p_pool, i_size, 2, 0);
        gst_object_unref (p_pool);
    }

    /* we support various metadata */
    gst_query_add_allocation_meta( p_query, GST_VIDEO_META_API_TYPE, NULL );

    return TRUE;

    /* ERRORS */
no_pool:
    {
        msg_Err( p_vsink->p_dec, "failed to create the pool" );
        return FALSE;
    }
no_caps:
    {
        msg_Err( p_vsink->p_dec, "no caps in allocation query" );
        return FALSE;
    }
invalid_caps:
    {
        msg_Err( p_vsink->p_dec, "invalid caps in allocation query" );
        return FALSE;
    }
}