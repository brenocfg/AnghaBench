#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* finalize ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  GstVlcPicturePlaneAllocator ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/ * GST_VLC_PICTURE_PLANE_ALLOCATOR (int /*<<< orphan*/ *) ; 
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_class ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gst_vlc_picture_plane_allocator_finalize( GObject *p_object )
{
    GstVlcPicturePlaneAllocator *p_alloc = GST_VLC_PICTURE_PLANE_ALLOCATOR(
            p_object );
    VLC_UNUSED( p_alloc );

    G_OBJECT_CLASS (parent_class)->finalize( p_object );
}