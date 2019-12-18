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
typedef  scalar_t__ guint ;
struct TYPE_2__ {int /*<<< orphan*/ * p_plane; int /*<<< orphan*/ * p_pic; } ;
typedef  int /*<<< orphan*/  GstVlcPicturePlaneAllocator ;
typedef  TYPE_1__ GstVlcPicturePlane ;
typedef  int /*<<< orphan*/  GstBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ gst_buffer_n_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ gst_buffer_peek_memory (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

void gst_vlc_picture_plane_allocator_release(
    GstVlcPicturePlaneAllocator *p_allocator, GstBuffer *p_buffer )
{
    VLC_UNUSED( p_allocator );

    GstVlcPicturePlane* p_mem =
        (GstVlcPicturePlane*) gst_buffer_peek_memory( p_buffer, 0 );
    guint i_plane;

    if( p_mem->p_pic )
    {
        picture_Release( p_mem->p_pic );

        for( i_plane = 0; i_plane < gst_buffer_n_memory( p_buffer );
                i_plane++ )
        {
            p_mem = (GstVlcPicturePlane*) gst_buffer_peek_memory ( p_buffer,
                    i_plane );
            p_mem->p_pic = NULL;
            p_mem->p_plane = NULL;
        }
    }
}