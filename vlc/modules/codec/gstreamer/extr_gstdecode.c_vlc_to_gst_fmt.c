#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_sar_den; scalar_t__ i_sar_num; int /*<<< orphan*/  i_frame_rate_base; scalar_t__ i_frame_rate; scalar_t__ i_height; scalar_t__ i_width; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_5__ {int i_codec; scalar_t__ i_extra; int /*<<< orphan*/  p_extra; TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;
typedef  int /*<<< orphan*/  GstStructure ;
typedef  char GstBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GST_MEMORY_FLAG_READONLY ; 
 int /*<<< orphan*/  GST_TYPE_BUFFER ; 
 int /*<<< orphan*/  GST_TYPE_FRACTION ; 
 int /*<<< orphan*/  G_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  G_TYPE_INT ; 
 int /*<<< orphan*/  G_TYPE_STRING ; 
#define  VLC_CODEC_FLV1 136 
#define  VLC_CODEC_H264 135 
#define  VLC_CODEC_MP4V 134 
#define  VLC_CODEC_MPGV 133 
#define  VLC_CODEC_VC1 132 
#define  VLC_CODEC_VP8 131 
#define  VLC_CODEC_WMV1 130 
#define  VLC_CODEC_WMV2 129 
#define  VLC_CODEC_WMV3 128 
 char* gst_buffer_new_wrapped_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_buffer_unref (char*) ; 
 int /*<<< orphan*/  gst_structure_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gst_structure_new_empty (char*) ; 
 int /*<<< orphan*/  gst_structure_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static GstStructure* vlc_to_gst_fmt( const es_format_t *p_fmt )
{
    const video_format_t *p_vfmt = &p_fmt->video;
    GstStructure *p_str = NULL;

    switch( p_fmt->i_codec ){
    case VLC_CODEC_H264:
        p_str = gst_structure_new_empty( "video/x-h264" );
        gst_structure_set( p_str, "alignment", G_TYPE_STRING, "au", NULL );
        if( p_fmt->i_extra )
            gst_structure_set( p_str, "stream-format", G_TYPE_STRING, "avc",
                    NULL );
        else
            gst_structure_set( p_str, "stream-format", G_TYPE_STRING,
                    "byte-stream", NULL );
        break;
    case VLC_CODEC_MP4V:
        p_str = gst_structure_new_empty( "video/mpeg" );
        gst_structure_set( p_str, "mpegversion", G_TYPE_INT, 4,
                "systemstream", G_TYPE_BOOLEAN, FALSE, NULL );
        break;
    case VLC_CODEC_VP8:
        p_str = gst_structure_new_empty( "video/x-vp8" );
        break;
    case VLC_CODEC_MPGV:
        p_str = gst_structure_new_empty( "video/mpeg" );
        gst_structure_set( p_str, "mpegversion", G_TYPE_INT, 2,
                "systemstream", G_TYPE_BOOLEAN, FALSE, NULL );
        break;
    case VLC_CODEC_FLV1:
        p_str = gst_structure_new_empty( "video/x-flash-video" );
        gst_structure_set( p_str, "flvversion", G_TYPE_INT, 1, NULL );
        break;
    case VLC_CODEC_WMV1:
        p_str = gst_structure_new_empty( "video/x-wmv" );
        gst_structure_set( p_str, "wmvversion", G_TYPE_INT, 1,
                "format", G_TYPE_STRING, "WMV1", NULL );
        break;
    case VLC_CODEC_WMV2:
        p_str = gst_structure_new_empty( "video/x-wmv" );
        gst_structure_set( p_str, "wmvversion", G_TYPE_INT, 2,
                "format", G_TYPE_STRING, "WMV2", NULL );
        break;
    case VLC_CODEC_WMV3:
        p_str = gst_structure_new_empty( "video/x-wmv" );
        gst_structure_set( p_str, "wmvversion", G_TYPE_INT, 3,
                "format", G_TYPE_STRING, "WMV3", NULL );
        break;
    case VLC_CODEC_VC1:
        p_str = gst_structure_new_empty( "video/x-wmv" );
        gst_structure_set( p_str, "wmvversion", G_TYPE_INT, 3,
                "format", G_TYPE_STRING, "WVC1", NULL );
        break;
    default:
        /* unsupported codec */
        return NULL;
    }

    if( p_vfmt->i_width && p_vfmt->i_height )
        gst_structure_set( p_str,
                "width", G_TYPE_INT, p_vfmt->i_width,
                "height", G_TYPE_INT, p_vfmt->i_height, NULL );

    if( p_vfmt->i_frame_rate && p_vfmt->i_frame_rate_base )
        gst_structure_set( p_str, "framerate", GST_TYPE_FRACTION,
                p_vfmt->i_frame_rate,
                p_vfmt->i_frame_rate_base, NULL );

    if( p_vfmt->i_sar_num && p_vfmt->i_sar_den )
        gst_structure_set( p_str, "pixel-aspect-ratio", GST_TYPE_FRACTION,
                p_vfmt->i_sar_num,
                p_vfmt->i_sar_den, NULL );

    if( p_fmt->i_extra )
    {
        GstBuffer *p_buf;

        p_buf = gst_buffer_new_wrapped_full( GST_MEMORY_FLAG_READONLY,
                p_fmt->p_extra, p_fmt->i_extra, 0,
                p_fmt->i_extra, NULL, NULL );
        if( p_buf == NULL )
        {
            gst_structure_free( p_str );
            return NULL;
        }

        gst_structure_set( p_str, "codec_data", GST_TYPE_BUFFER, p_buf, NULL );
        gst_buffer_unref( p_buf );
    }

    return p_str;
}