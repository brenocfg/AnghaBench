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

/* Variables and functions */

__attribute__((used)) static inline unsigned opus_frame_duration(unsigned char *data, long len)
{
    static const int silk_fs_div[4] = { 6000, 3000, 1500, 1000 };
    unsigned toc;
    unsigned nframes;
    unsigned frame_size;
    unsigned nsamples;
    unsigned i_rate;
    if( len < 1 )
        return 0;
    toc = data[0];
    switch( toc&3 )
    {
        case 0:
            nframes = 1;
            break;
        case 1:
        case 2:
            nframes = 2;
            break;
        default:
            if( len < 2 )
                return 0;
            nframes = data[1]&0x3F;
            break;
    }
    i_rate = 48000;
    if( toc&0x80 )
        frame_size = (i_rate << (toc >> 3 & 3)) / 400;
    else if( ( toc&0x60 ) == 0x60 )
        frame_size = i_rate/(100 >> (toc >> 3 & 1));
    else
        frame_size = i_rate*60 / silk_fs_div[toc >> 3 & 3];
    nsamples = nframes*frame_size;
    if( nsamples*25 > i_rate*3 )
        return 0;
    return nsamples;
}