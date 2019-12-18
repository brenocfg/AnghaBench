#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* acquire_buffer ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoPool ;
typedef  scalar_t__ GstFlowReturn ;
typedef  int /*<<< orphan*/  GstBufferPoolAcquireParams ;
typedef  int /*<<< orphan*/  GstBufferPool ;
typedef  int /*<<< orphan*/  GstBuffer ;

/* Variables and functions */
 TYPE_3__* GST_BUFFER_POOL_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ GST_FLOW_EOS ; 
 scalar_t__ GST_FLOW_OK ; 
 TYPE_1__* GST_VLC_VIDEO_POOL_CAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_class ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GstFlowReturn gst_vlc_video_pool_acquire_buffer( GstBufferPool *p_pool,
        GstBuffer **p_buffer, GstBufferPoolAcquireParams *p_params )
{
    GstVlcVideoPool *p_vpool = GST_VLC_VIDEO_POOL_CAST( p_pool );
    GstFlowReturn result;

    result = GST_BUFFER_POOL_CLASS( parent_class)->acquire_buffer( p_pool,
            p_buffer, p_params );

    if( result == GST_FLOW_OK &&
            !gst_vlc_picture_plane_allocator_hold( p_vpool->p_allocator,
                *p_buffer ))
        result = GST_FLOW_EOS;

    return result;
}