#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ i_chroma; int /*<<< orphan*/  i_bmask; int /*<<< orphan*/  i_gmask; int /*<<< orphan*/  i_rmask; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_RGB24 ; 
 scalar_t__ VLC_CODEC_RGB32 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int vlc_ctz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int GetPackedRgbIndexes( const video_format_t *p_fmt, int *i_r_index,
                                      int *i_g_index, int *i_b_index )
{
    if( p_fmt->i_chroma != VLC_CODEC_RGB24 && p_fmt->i_chroma != VLC_CODEC_RGB32 )
        return VLC_EGENERIC;

#ifdef WORDS_BIGENDIAN
    const int i_mask_bits = p_fmt->i_chroma == VLC_CODEC_RGB24 ? 16 : 24;
    *i_r_index = (i_mask_bits - vlc_ctz(p_fmt->i_rmask)) / 8;
    *i_g_index = (i_mask_bits - vlc_ctz(p_fmt->i_gmask)) / 8;
    *i_b_index = (i_mask_bits - vlc_ctz(p_fmt->i_bmask)) / 8;
#else
    *i_r_index = vlc_ctz(p_fmt->i_rmask) / 8;
    *i_g_index = vlc_ctz(p_fmt->i_gmask) / 8;
    *i_b_index = vlc_ctz(p_fmt->i_bmask) / 8;
#endif
    return VLC_SUCCESS;
}