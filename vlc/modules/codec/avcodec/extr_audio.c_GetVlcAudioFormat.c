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
typedef  int /*<<< orphan*/  const vlc_fourcc_t ;
typedef  int /*<<< orphan*/  fcc ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 142 
#define  AV_SAMPLE_FMT_DBLP 141 
#define  AV_SAMPLE_FMT_FLT 140 
#define  AV_SAMPLE_FMT_FLTP 139 
#define  AV_SAMPLE_FMT_S16 138 
#define  AV_SAMPLE_FMT_S16P 137 
#define  AV_SAMPLE_FMT_S32 136 
#define  AV_SAMPLE_FMT_S32P 135 
#define  AV_SAMPLE_FMT_U8 134 
#define  AV_SAMPLE_FMT_U8P 133 
#define  VLC_CODEC_FL32 132 
#define  VLC_CODEC_FL64 131 
#define  VLC_CODEC_S16N 130 
#define  VLC_CODEC_S32N 129 
#define  VLC_CODEC_U8 128 

vlc_fourcc_t GetVlcAudioFormat( int fmt )
{
    static const vlc_fourcc_t fcc[] = {
        [AV_SAMPLE_FMT_U8]    = VLC_CODEC_U8,
        [AV_SAMPLE_FMT_S16]   = VLC_CODEC_S16N,
        [AV_SAMPLE_FMT_S32]   = VLC_CODEC_S32N,
        [AV_SAMPLE_FMT_FLT]   = VLC_CODEC_FL32,
        [AV_SAMPLE_FMT_DBL]   = VLC_CODEC_FL64,
        [AV_SAMPLE_FMT_U8P]   = VLC_CODEC_U8,
        [AV_SAMPLE_FMT_S16P]  = VLC_CODEC_S16N,
        [AV_SAMPLE_FMT_S32P]  = VLC_CODEC_S32N,
        [AV_SAMPLE_FMT_FLTP]  = VLC_CODEC_FL32,
        [AV_SAMPLE_FMT_DBLP]  = VLC_CODEC_FL64,
    };
    if( (sizeof(fcc) / sizeof(fcc[0])) > (unsigned)fmt )
        return fcc[fmt];
    return VLC_CODEC_S16N;
}