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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 size_t __MIN (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 

__attribute__((used)) static void CopyPlane(uint8_t *dst, size_t dst_pitch,
                      const uint8_t *src, size_t src_pitch,
                      unsigned height, int bitshift)
{
    const size_t copy_pitch = __MIN(src_pitch, dst_pitch);
    if (bitshift != 0)
    {
        for (unsigned y = 0; y < height; y++)
        {
            uint16_t *dst16 = (uint16_t *) dst;
            const uint16_t *src16 = (const uint16_t *) src;

            if (bitshift > 0)
                for (unsigned x = 0; x < (copy_pitch / 2); x++)
                    *dst16++ = (*src16++) >> (bitshift & 0xf);
            else
                for (unsigned x = 0; x < (copy_pitch / 2); x++)
                    *dst16++ = (*src16++) << ((-bitshift) & 0xf);
            src += src_pitch;
            dst += dst_pitch;
        }
    }
    else if (src_pitch == dst_pitch)
        memcpy(dst, src, copy_pitch * height);
    else
    for (unsigned y = 0; y < height; y++) {
        memcpy(dst, src, copy_pitch);
        src += src_pitch;
        dst += dst_pitch;
    }
}