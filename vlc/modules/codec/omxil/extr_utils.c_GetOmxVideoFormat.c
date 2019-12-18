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
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_2__ {scalar_t__ i_codec; scalar_t__ i_fourcc; } ;
typedef  scalar_t__ OMX_VIDEO_CODINGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
 TYPE_1__* video_format_table ; 
 scalar_t__ vlc_fourcc_GetCodec (int /*<<< orphan*/ ,scalar_t__) ; 
 char* vlc_fourcc_GetDescription (int /*<<< orphan*/ ,scalar_t__) ; 

int GetOmxVideoFormat( vlc_fourcc_t i_fourcc,
                       OMX_VIDEO_CODINGTYPE *pi_omx_codec,
                       const char **ppsz_name )
{
    unsigned int i;

    i_fourcc = vlc_fourcc_GetCodec( VIDEO_ES, i_fourcc );

    for( i = 0; video_format_table[i].i_codec != 0; i++ )
        if( video_format_table[i].i_fourcc == i_fourcc ) break;

    if( pi_omx_codec ) *pi_omx_codec = video_format_table[i].i_codec;
    if( ppsz_name ) *ppsz_name = vlc_fourcc_GetDescription( VIDEO_ES, i_fourcc );
    return !!video_format_table[i].i_codec;
}