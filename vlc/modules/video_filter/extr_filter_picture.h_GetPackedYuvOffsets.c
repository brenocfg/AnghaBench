#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vlc_fourcc_t ;

/* Variables and functions */
#define  VLC_CODEC_UYVY 131 
#define  VLC_CODEC_VYUY 130 
#define  VLC_CODEC_YUYV 129 
#define  VLC_CODEC_YVYU 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static inline int GetPackedYuvOffsets( vlc_fourcc_t i_chroma,
    int *i_y_offset, int *i_u_offset, int *i_v_offset )
{
    switch( i_chroma )
    {
        case VLC_CODEC_UYVY:
            /* UYVY */
            *i_y_offset = 1;
            *i_u_offset = 0;
            *i_v_offset = 2;
            return VLC_SUCCESS;
        case VLC_CODEC_VYUY:
            /* VYUY */
            *i_y_offset = 1;
            *i_u_offset = 2;
            *i_v_offset = 0;
            return VLC_SUCCESS;
        case VLC_CODEC_YUYV:
            /* YUYV */
            *i_y_offset = 0;
            *i_u_offset = 1;
            *i_v_offset = 3;
            return VLC_SUCCESS;
        case VLC_CODEC_YVYU:
            /* YVYU */
            *i_y_offset = 0;
            *i_u_offset = 3;
            *i_v_offset = 1;
            return VLC_SUCCESS;
        default:
            return VLC_EGENERIC;
    }
}