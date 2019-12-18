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
typedef  int uint8_t ;
struct flac_stream_info {int min_framesize; int max_framesize; int sample_rate; int channels; int bits_per_sample; int total_samples; void* max_blocksize; void* min_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC_FRAME_SIZE_MIN ; 
 int GetDWBE (int const*) ; 
 int GetQWBE (int const*) ; 
 void* GetWBE (int const*) ; 
 int INT64_C (int) ; 
 void* VLC_CLIP (void*,int,int) ; 
 int __MAX (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void FLAC_ParseStreamInfo( const uint8_t *p_buf,
                                         struct flac_stream_info *stream_info )
{
    stream_info->min_blocksize = GetWBE( &p_buf[0] );
    stream_info->min_blocksize = VLC_CLIP( stream_info->min_blocksize, 16, 65535 );

    stream_info->max_blocksize = GetWBE( &p_buf[2] );
    stream_info->max_blocksize = VLC_CLIP( stream_info->max_blocksize, 16, 65535 );

    stream_info->min_framesize = GetDWBE( &p_buf[3] ) & 0x00FFFFFF;
    stream_info->min_framesize = __MAX( stream_info->min_framesize, FLAC_FRAME_SIZE_MIN );

    stream_info->max_framesize = GetDWBE( &p_buf[6] ) & 0x00FFFFFF;

    stream_info->sample_rate = GetDWBE( &p_buf[10] ) >> 12;
    stream_info->channels = (p_buf[12] & 0x0F >> 1) + 1;
    stream_info->bits_per_sample = (((p_buf[12] & 0x01) << 4) | p_buf[13] >> 4) + 1;

    stream_info->total_samples = GetQWBE(&p_buf[4+6]) & ((INT64_C(1)<<36)-1);
}