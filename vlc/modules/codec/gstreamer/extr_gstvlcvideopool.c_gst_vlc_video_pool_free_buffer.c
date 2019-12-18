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
struct TYPE_5__ {int /*<<< orphan*/  (* free_buffer ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  p_dec; int /*<<< orphan*/  p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoPool ;
typedef  int /*<<< orphan*/  GstBufferPool ;
typedef  int /*<<< orphan*/  GstBuffer ;

/* Variables and functions */
 TYPE_3__* GST_BUFFER_POOL_CLASS (int /*<<< orphan*/ ) ; 
 TYPE_1__* GST_VLC_VIDEO_POOL_CAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_class ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gst_vlc_video_pool_free_buffer( GstBufferPool *p_pool,
        GstBuffer *p_buffer )
{
    GstVlcVideoPool* p_vpool = GST_VLC_VIDEO_POOL_CAST( p_pool );

    gst_vlc_picture_plane_allocator_release( p_vpool->p_allocator, p_buffer );

    msg_Dbg( p_vpool->p_dec, "freed buffer %p", p_buffer );

    GST_BUFFER_POOL_CLASS( parent_class )->free_buffer( p_pool, p_buffer );

    return;
}