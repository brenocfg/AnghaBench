#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  finalize; } ;
struct TYPE_3__ {int /*<<< orphan*/  free; int /*<<< orphan*/  alloc; } ;
typedef  int /*<<< orphan*/  GstVlcPicturePlaneAllocatorClass ;
typedef  TYPE_1__ GstAllocatorClass ;
typedef  TYPE_2__ GObjectClass ;

/* Variables and functions */
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_dummy_alloc ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_finalize ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_free ; 

__attribute__((used)) static void gst_vlc_picture_plane_allocator_class_init(
    GstVlcPicturePlaneAllocatorClass *p_klass )
{
    GObjectClass *p_gobject_class;
    GstAllocatorClass *p_allocator_class;

    p_gobject_class = (GObjectClass*) p_klass;
    p_allocator_class = (GstAllocatorClass*) p_klass;

    p_gobject_class->finalize = gst_vlc_picture_plane_allocator_finalize;

    p_allocator_class->alloc = gst_vlc_picture_plane_allocator_dummy_alloc;
    p_allocator_class->free = gst_vlc_picture_plane_allocator_free;
}