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
struct TYPE_4__ {int /*<<< orphan*/ * p_dec; int /*<<< orphan*/  p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoPool ;
typedef  int /*<<< orphan*/  GstAllocator ;

/* Variables and functions */
 int /*<<< orphan*/  GST_IS_VLC_PICTURE_PLANE_ALLOCATOR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GST_TYPE_VLC_VIDEO_POOL ; 
 TYPE_1__* g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

GstVlcVideoPool* gst_vlc_video_pool_new(
    GstAllocator *p_allocator, decoder_t *p_dec )
{
    GstVlcVideoPool *p_pool;

    if( !GST_IS_VLC_PICTURE_PLANE_ALLOCATOR( p_allocator ))
    {
        msg_Err( p_dec, "unspported allocator for pool" );
        return NULL;
    }

    p_pool = g_object_new( GST_TYPE_VLC_VIDEO_POOL, NULL );
    p_pool->p_allocator = gst_object_ref( p_allocator );
    p_pool->p_dec = p_dec;

    return p_pool;
}