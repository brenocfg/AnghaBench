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
typedef  int /*<<< orphan*/  GLenum ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 unsigned int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ptx_compress_dxtn (int,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline BOOL x1r5g5b5_to_dxtn(const BYTE *src, BYTE *dst, DWORD pitch_in,
        DWORD pitch_out, unsigned int w, unsigned int h, GLenum destformat, BOOL alpha)
{
    static const unsigned char convert_5to8[] =
    {
        0x00, 0x08, 0x10, 0x19, 0x21, 0x29, 0x31, 0x3a,
        0x42, 0x4a, 0x52, 0x5a, 0x63, 0x6b, 0x73, 0x7b,
        0x84, 0x8c, 0x94, 0x9c, 0xa5, 0xad, 0xb5, 0xbd,
        0xc5, 0xce, 0xd6, 0xde, 0xe6, 0xef, 0xf7, 0xff,
    };
    unsigned int x, y;
    DWORD *tmp;
    WORD color;

    TRACE("Converting %ux%u pixels, pitches %u %u.\n", w, h, pitch_in, pitch_out);

    tmp = HeapAlloc(GetProcessHeap(), 0, h * w * sizeof(DWORD));
    if (!tmp)
    {
        ERR("Failed to allocate memory for conversion\n");
        return FALSE;
    }

    for (y = 0; y < h; ++y)
    {
        const WORD *src_line = (const WORD *)(src + y * pitch_in);
        DWORD *dst_line = tmp + y * w;
        for (x = 0; x < w; ++x)
        {
            color = src_line[x];
            if (alpha)
            {
                dst_line[x] = ((color & 0x8000) ? 0xff000000 : 0) |
                              convert_5to8[(color & 0x001f)] << 16 |
                              convert_5to8[(color & 0x03e0) >> 5] << 8 |
                              convert_5to8[(color & 0x7c00) >> 10];
            }
            else
            {
                dst_line[x] = 0xff000000 |
                              convert_5to8[(color & 0x001f)] << 16 |
                              convert_5to8[(color & 0x03e0) >> 5] << 8 |
                              convert_5to8[(color & 0x7c00) >> 10];
            }
        }
    }

    ptx_compress_dxtn(4, w, h, (BYTE *)tmp, destformat, dst, pitch_out);
    HeapFree(GetProcessHeap(), 0, tmp);
    return TRUE;
}