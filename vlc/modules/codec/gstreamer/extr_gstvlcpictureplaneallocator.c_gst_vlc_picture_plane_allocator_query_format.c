#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_7__ {int /*<<< orphan*/  video; } ;
struct TYPE_8__ {TYPE_1__ fmt_out; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_9__ {TYPE_2__* p_dec; int /*<<< orphan*/  pic_info; } ;
typedef  TYPE_3__ GstVlcPicturePlaneAllocator ;
typedef  int /*<<< orphan*/  GstVideoInfo ;
typedef  int /*<<< orphan*/  GstVideoAlignment ;
typedef  int /*<<< orphan*/  GstCaps ;

/* Variables and functions */
 int gst_vlc_video_info_from_vout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool gst_vlc_picture_plane_allocator_query_format(
        GstVlcPicturePlaneAllocator *p_allocator, GstVideoInfo *p_info,
        GstVideoAlignment *p_align, GstCaps *p_caps )
{
    decoder_t *p_dec = p_allocator->p_dec;
    video_format_t v_fmt;
    picture_t *p_pic_info = &p_allocator->pic_info;

    /* Back up the original format; as this is just a query  */
    v_fmt = p_dec->fmt_out.video;
    video_format_Init( &p_dec->fmt_out.video, 0 );

    bool b_ret =
        gst_vlc_video_info_from_vout( p_info, p_align, p_caps, p_dec,
                p_pic_info );

    video_format_Clean( &p_dec->fmt_out.video );

    /* Restore the original format; as this was just a query  */
    p_dec->fmt_out.video = v_fmt;

    if( !b_ret )
    {
        msg_Err( p_allocator->p_dec, "failed to get the vout info" );
        return false;
    }

    return true;
}