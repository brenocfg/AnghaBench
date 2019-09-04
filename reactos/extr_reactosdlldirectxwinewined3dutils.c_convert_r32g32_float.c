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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_r32g32_float(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    unsigned int x, y, z;
    const float *Source;
    float *Dest;

    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; y++)
        {
            Source = (const float *)(src + z * src_slice_pitch + y * src_row_pitch);
            Dest = (float *) (dst + z * dst_slice_pitch + y * dst_row_pitch);
            for (x = 0; x < width; x++ )
            {
                float green = (*Source++);
                float red = (*Source++);
                Dest[0] = green;
                Dest[1] = red;
                Dest[2] = 1.0f;
                Dest += 3;
            }
        }
    }
}