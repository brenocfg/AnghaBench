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
typedef  int LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  unsigned char BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_r8g8b8a8_snorm(const BYTE *src, BYTE *dst, UINT src_row_pitch, UINT src_slice_pitch,
        UINT dst_row_pitch, UINT dst_slice_pitch, UINT width, UINT height, UINT depth)
{
    unsigned int x, y, z;
    const DWORD *Source;
    unsigned char *Dest;

    for (z = 0; z < depth; z++)
    {
        for (y = 0; y < height; y++)
        {
            Source = (const DWORD *)(src + z * src_slice_pitch + y * src_row_pitch);
            Dest = dst + z * dst_slice_pitch + y * dst_row_pitch;
            for (x = 0; x < width; x++ )
            {
                LONG color = (*Source++);
                /* B */ Dest[0] = ((color >> 16) & 0xff) + 128; /* W */
                /* G */ Dest[1] = ((color >> 8 ) & 0xff) + 128; /* V */
                /* R */ Dest[2] = (color         & 0xff) + 128; /* U */
                /* A */ Dest[3] = ((color >> 24) & 0xff) + 128; /* Q */
                Dest += 4;
            }
        }
    }
}