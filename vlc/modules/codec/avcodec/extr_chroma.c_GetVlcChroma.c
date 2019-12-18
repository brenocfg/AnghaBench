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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ i_chroma; int /*<<< orphan*/  i_bmask; int /*<<< orphan*/  i_gmask; int /*<<< orphan*/  i_rmask; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_6__ {scalar_t__ i_chroma; int i_chroma_id; int /*<<< orphan*/  i_bmask; int /*<<< orphan*/  i_gmask; int /*<<< orphan*/  i_rmask; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_3__* chroma_table ; 
 int /*<<< orphan*/  video_format_FixRgb (TYPE_1__*) ; 

int GetVlcChroma( video_format_t *fmt, int i_ffmpeg_chroma )
{
    for( int i = 0; chroma_table[i].i_chroma != 0; i++ )
    {
        if( chroma_table[i].i_chroma_id == i_ffmpeg_chroma )
        {
            fmt->i_rmask = chroma_table[i].i_rmask;
            fmt->i_gmask = chroma_table[i].i_gmask;
            fmt->i_bmask = chroma_table[i].i_bmask;
            fmt->i_chroma = chroma_table[i].i_chroma;
            video_format_FixRgb( fmt );
            return VLC_SUCCESS;
        }
    }
    return VLC_EGENERIC;
}