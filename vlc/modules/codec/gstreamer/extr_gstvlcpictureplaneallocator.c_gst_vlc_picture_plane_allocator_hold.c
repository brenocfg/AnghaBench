#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_planes; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_8__ {int /*<<< orphan*/ * p_plane; TYPE_1__* p_pic; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p_dec; } ;
typedef  TYPE_2__ GstVlcPicturePlaneAllocator ;
typedef  TYPE_3__ GstVlcPicturePlane ;
typedef  int /*<<< orphan*/  GstBuffer ;

/* Variables and functions */
 TYPE_1__* decoder_NewPicture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_UpdateVideoFormat (int /*<<< orphan*/ *) ; 
 scalar_t__ gst_buffer_peek_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

bool gst_vlc_picture_plane_allocator_hold(
    GstVlcPicturePlaneAllocator *p_allocator, GstBuffer *p_buffer )
{
    picture_t* p_pic = NULL;
    decoder_t* p_dec = p_allocator->p_dec;
    GstVlcPicturePlane *p_mem;
    int i_plane;

    if( !decoder_UpdateVideoFormat( p_dec ) )
        p_pic = decoder_NewPicture( p_dec );
    if( !p_pic )
    {
        msg_Err( p_allocator->p_dec, "failed to acquire picture from vout" );
        return false;
    }

    for( i_plane = 0; i_plane < p_pic->i_planes; i_plane++ )
    {
        p_mem = (GstVlcPicturePlane*) gst_buffer_peek_memory ( p_buffer,
                i_plane );
        p_mem->p_pic = p_pic;
        p_mem->p_plane = &p_pic->p[ i_plane ];
    }

    return true;
}