#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/ * gpointer ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_6__ {TYPE_2__ parent; TYPE_1__* p_plane; scalar_t__ p_pic; } ;
struct TYPE_4__ {scalar_t__ p_pixels; } ;
typedef  TYPE_3__ GstVlcPicturePlane ;
typedef  int /*<<< orphan*/  GstMemory ;
typedef  int /*<<< orphan*/  GstMapFlags ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gpointer gst_vlc_picture_plane_map( GstMemory *p_gmem,
    gsize i_maxsize, GstMapFlags flags )
{
    VLC_UNUSED( i_maxsize );
    VLC_UNUSED( flags );
    GstVlcPicturePlane* p_mem = (GstVlcPicturePlane*) p_gmem;

    if( p_mem->p_pic )
        return (gpointer) (p_mem->p_plane->p_pixels + p_mem->parent.offset);
    else
        return NULL;
}