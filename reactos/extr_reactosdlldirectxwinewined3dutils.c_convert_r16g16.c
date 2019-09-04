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
typedef  int WORD ;
typedef  unsigned int UINT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_r16g16(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    unsigned int x, y, z;
    const WORD *Source;
    WORD *Dest;

    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; y++)
        {
            Source = (const WORD *)(src + z * src_slice_pitch + y * src_row_pitch);
            Dest = (WORD *) (dst + z * dst_slice_pitch + y * dst_row_pitch);
            for (x = 0; x < width; x++ )
            {
                WORD green = (*Source++);
                WORD red = (*Source++);
                Dest[0] = green;
                Dest[1] = red;
                /* Strictly speaking not correct for R16G16F, but it doesn't matter because the
                 * shader overwrites it anyway */
                Dest[2] = 0xffff;
                Dest += 3;
            }
        }
    }
}