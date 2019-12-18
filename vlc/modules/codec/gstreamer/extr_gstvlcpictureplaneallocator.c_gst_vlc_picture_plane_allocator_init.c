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
struct TYPE_3__ {int /*<<< orphan*/  mem_copy; int /*<<< orphan*/  mem_unmap; int /*<<< orphan*/  mem_map; int /*<<< orphan*/  mem_type; } ;
typedef  int /*<<< orphan*/  GstVlcPicturePlaneAllocator ;
typedef  TYPE_1__ GstAllocator ;

/* Variables and functions */
 TYPE_1__* GST_ALLOCATOR_CAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GST_ALLOCATOR_FLAG_CUSTOM_ALLOC ; 
 int /*<<< orphan*/  GST_OBJECT_FLAG_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GST_VLC_PICTURE_PLANE_ALLOCATOR_NAME ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_copy ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_map ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_unmap ; 

__attribute__((used)) static void gst_vlc_picture_plane_allocator_init(
        GstVlcPicturePlaneAllocator *p_allocator )
{
    GstAllocator *p_alloc = GST_ALLOCATOR_CAST( p_allocator );

    p_alloc->mem_type = GST_VLC_PICTURE_PLANE_ALLOCATOR_NAME;
    p_alloc->mem_map = gst_vlc_picture_plane_map;
    p_alloc->mem_unmap = gst_vlc_picture_plane_unmap;
    p_alloc->mem_copy = gst_vlc_picture_plane_copy;
    /* fallback is_span */

    GST_OBJECT_FLAG_SET( p_allocator, GST_ALLOCATOR_FLAG_CUSTOM_ALLOC );
}