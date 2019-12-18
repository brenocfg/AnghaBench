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
 int PRIV_WINDOW_FORMAT_YV12 ; 
#define  VLC_CODEC_I420 132 
#define  VLC_CODEC_RGB16 131 
#define  VLC_CODEC_RGB32 130 
#define  VLC_CODEC_RGBA 129 
#define  VLC_CODEC_YV12 128 
 int WINDOW_FORMAT_RGBA_8888 ; 
 int WINDOW_FORMAT_RGBX_8888 ; 
 int WINDOW_FORMAT_RGB_565 ; 

__attribute__((used)) static inline int ChromaToAndroidHal(vlc_fourcc_t i_chroma)
{
    switch (i_chroma) {
        case VLC_CODEC_YV12:
        case VLC_CODEC_I420:
            return PRIV_WINDOW_FORMAT_YV12;
        case VLC_CODEC_RGB16:
            return WINDOW_FORMAT_RGB_565;
        case VLC_CODEC_RGB32:
            return WINDOW_FORMAT_RGBX_8888;
        case VLC_CODEC_RGBA:
            return WINDOW_FORMAT_RGBA_8888;
        default:
            return -1;
    }
}