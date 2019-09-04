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
typedef  unsigned int UINT ;
typedef  unsigned char BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_l4a4_unorm(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    /* WINED3DFMT_L4A4_UNORM exists as an internal gl format, but for some reason there is not
     * format+type combination to load it. Thus convert it to A8L8, then load it
     * with A4L4 internal, but A8L8 format+type
     */
    unsigned int x, y, z;
    const unsigned char *Source;
    unsigned char *Dest;

    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; y++)
        {
            Source = src + z * src_slice_pitch + y * src_row_pitch;
            Dest = dst + z * dst_slice_pitch + y * dst_row_pitch;
            for (x = 0; x < width; x++ )
            {
                unsigned char color = (*Source++);
                /* A */ Dest[1] = (color & 0xf0u) << 0;
                /* L */ Dest[0] = (color & 0x0fu) << 4;
                Dest += 2;
            }
        }
    }
}