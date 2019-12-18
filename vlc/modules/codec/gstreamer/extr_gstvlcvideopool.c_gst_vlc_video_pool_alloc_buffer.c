#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {int /*<<< orphan*/  p_dec; scalar_t__ b_add_metavideo; int /*<<< orphan*/  p_allocator; TYPE_2__ info; } ;
typedef  TYPE_1__ GstVlcVideoPool ;
typedef  TYPE_2__ GstVideoInfo ;
typedef  int /*<<< orphan*/  GstFlowReturn ;
typedef  int /*<<< orphan*/  GstBufferPoolAcquireParams ;
typedef  int /*<<< orphan*/  GstBufferPool ;
typedef  int /*<<< orphan*/  GstBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GST_FLOW_EOS ; 
 int /*<<< orphan*/  GST_FLOW_OK ; 
 int /*<<< orphan*/  GST_VIDEO_FRAME_FLAG_NONE ; 
 int /*<<< orphan*/  GST_VIDEO_INFO_FORMAT (TYPE_2__*) ; 
 int /*<<< orphan*/  GST_VIDEO_INFO_HEIGHT (TYPE_2__*) ; 
 int /*<<< orphan*/  GST_VIDEO_INFO_N_PLANES (TYPE_2__*) ; 
 int /*<<< orphan*/  GST_VIDEO_INFO_WIDTH (TYPE_2__*) ; 
 TYPE_1__* GST_VLC_VIDEO_POOL_CAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_buffer_add_video_meta_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gst_buffer_new () ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static GstFlowReturn gst_vlc_video_pool_alloc_buffer( GstBufferPool *p_pool,
        GstBuffer **p_buffer, GstBufferPoolAcquireParams *p_params)
{
    VLC_UNUSED( p_params );

    GstVlcVideoPool *p_vpool = GST_VLC_VIDEO_POOL_CAST( p_pool );
    GstVideoInfo *p_info = &p_vpool->info;

    *p_buffer = gst_buffer_new( );

    if( !gst_vlc_picture_plane_allocator_alloc( p_vpool->p_allocator,
                *p_buffer ))
    {
        msg_Err( p_vpool->p_dec, "buffer allocation failed" );
        return GST_FLOW_EOS;
    }

    if( p_vpool->b_add_metavideo )
    {
        msg_Dbg( p_vpool->p_dec, "meta video enabled" );
        gst_buffer_add_video_meta_full( *p_buffer, GST_VIDEO_FRAME_FLAG_NONE,
                GST_VIDEO_INFO_FORMAT( p_info ), GST_VIDEO_INFO_WIDTH( p_info ),
                GST_VIDEO_INFO_HEIGHT( p_info ),
                GST_VIDEO_INFO_N_PLANES( p_info ),
                p_info->offset, p_info->stride );
    }

    msg_Dbg( p_vpool->p_dec, "allocated buffer %p", *p_buffer );

    return GST_FLOW_OK;
}