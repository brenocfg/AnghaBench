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
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  pfetch_2d_texel_rgba_dxt1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,unsigned int,unsigned int*) ; 

__attribute__((used)) static inline BOOL dxt1_to_x8r8g8b8(const BYTE *src, BYTE *dst, DWORD pitch_in,
        DWORD pitch_out, unsigned int w, unsigned int h, BOOL alpha)
{
    unsigned int x, y;
    DWORD color;

    TRACE("Converting %ux%u pixels, pitches %u %u\n", w, h, pitch_in, pitch_out);

    for (y = 0; y < h; ++y)
    {
        DWORD *dst_line = (DWORD *)(dst + y * pitch_out);
        for (x = 0; x < w; ++x)
        {
            /* pfetch_2d_texel_rgba_dxt1 doesn't correctly handle pitch */
            pfetch_2d_texel_rgba_dxt1(0, src + (y / 4) * pitch_in + (x / 4) * 8,
                                      x & 3, y & 3, &color);
            if (alpha)
            {
                dst_line[x] = (color & 0xff00ff00) | ((color & 0xff) << 16) |
                              ((color & 0xff0000) >> 16);
            }
            else
            {
                dst_line[x] = 0xff000000 | ((color & 0xff) << 16) |
                              (color & 0xff00) | ((color & 0xff0000) >> 16);
            }
        }
    }

    return TRUE;
}