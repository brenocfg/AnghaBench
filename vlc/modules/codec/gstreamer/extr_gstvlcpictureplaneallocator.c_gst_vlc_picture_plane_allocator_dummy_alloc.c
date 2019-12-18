#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * gsize ;
typedef  int /*<<< orphan*/  GstMemory ;
typedef  int /*<<< orphan*/  GstAllocator ;
typedef  int /*<<< orphan*/  GstAllocationParams ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GstMemory* gst_vlc_picture_plane_allocator_dummy_alloc(
        GstAllocator* p_allocator, gsize i_size, GstAllocationParams *p_params )
{
    VLC_UNUSED( p_allocator );
    VLC_UNUSED( i_size );
    VLC_UNUSED( p_params );
    return NULL;
}