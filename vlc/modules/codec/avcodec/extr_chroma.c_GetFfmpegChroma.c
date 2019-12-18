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
struct TYPE_4__ {scalar_t__ i_chroma; scalar_t__ i_rmask; scalar_t__ i_gmask; scalar_t__ i_bmask; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_5__ {scalar_t__ i_chroma; scalar_t__ i_rmask; scalar_t__ i_gmask; scalar_t__ i_bmask; int i_chroma_id; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_2__* chroma_table ; 

int GetFfmpegChroma( int *restrict i_ffmpeg_chroma, const video_format_t *fmt )
{
    for( int i = 0; chroma_table[i].i_chroma != 0; i++ )
    {
        if( chroma_table[i].i_chroma == fmt->i_chroma )
        {
            if( ( chroma_table[i].i_rmask == 0 &&
                  chroma_table[i].i_gmask == 0 &&
                  chroma_table[i].i_bmask == 0 ) ||
                ( chroma_table[i].i_rmask == fmt->i_rmask &&
                  chroma_table[i].i_gmask == fmt->i_gmask &&
                  chroma_table[i].i_bmask == fmt->i_bmask ) )
            {
                *i_ffmpeg_chroma = chroma_table[i].i_chroma_id;
                return VLC_SUCCESS;
            }
        }
    }
    return VLC_EGENERIC;
}