#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ i_chroma; scalar_t__ i_rmask; scalar_t__ i_gmask; scalar_t__ i_bmask; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_RGB15 ; 
 scalar_t__ VLC_CODEC_RGB16 ; 
 scalar_t__ VLC_CODEC_RGB24 ; 
 scalar_t__ VLC_CODEC_RGB32 ; 
 int /*<<< orphan*/  video_format_FixRgb (TYPE_1__*) ; 

__attribute__((used)) static bool BitMapFormatIsSimilar( const video_format_t *f1,
                                   const video_format_t *f2 )
{
    if( f1->i_chroma == VLC_CODEC_RGB15 ||
        f1->i_chroma == VLC_CODEC_RGB16 ||
        f1->i_chroma == VLC_CODEC_RGB24 ||
        f1->i_chroma == VLC_CODEC_RGB32 )
    {
        video_format_t v1 = *f1;
        video_format_t v2 = *f2;

        video_format_FixRgb( &v1 );
        video_format_FixRgb( &v2 );

        if( v1.i_rmask != v2.i_rmask ||
            v1.i_gmask != v2.i_gmask ||
            v1.i_bmask != v2.i_bmask )
            return false;
    }
    return true;
}