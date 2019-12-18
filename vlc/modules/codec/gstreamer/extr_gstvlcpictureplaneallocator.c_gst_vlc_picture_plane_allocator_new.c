#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_dec; } ;
typedef  TYPE_1__ GstVlcPicturePlaneAllocator ;

/* Variables and functions */
 int /*<<< orphan*/  GST_TYPE_VLC_PICTURE_PLANE_ALLOCATOR ; 
 TYPE_1__* g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

GstVlcPicturePlaneAllocator* gst_vlc_picture_plane_allocator_new(
        decoder_t *p_dec )
{
    GstVlcPicturePlaneAllocator *p_allocator;

    p_allocator = g_object_new( GST_TYPE_VLC_PICTURE_PLANE_ALLOCATOR, NULL);
    p_allocator->p_dec = p_dec;

    return p_allocator;
}