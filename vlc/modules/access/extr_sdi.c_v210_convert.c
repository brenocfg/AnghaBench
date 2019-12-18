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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PIXELS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_le2ne32 (int /*<<< orphan*/ ) ; 

void v210_convert(uint16_t *dst, const uint32_t *bytes, const int width, const int height)
{
    const int stride = ((width + 47) / 48) * 48 * 8 / 3 / 4;
    uint16_t *y = &dst[0];
    uint16_t *u = &dst[width * height * 2 / 2];
    uint16_t *v = &dst[width * height * 3 / 2];

#define READ_PIXELS(a, b, c)         \
    do {                             \
        val  = av_le2ne32(*src++);   \
        *a++ =  val & 0x3FF;         \
        *b++ = (val >> 10) & 0x3FF;  \
        *c++ = (val >> 20) & 0x3FF;  \
    } while (0)

    for (int h = 0; h < height; h++) {
        const uint32_t *src = bytes;
        uint32_t val = 0;
        int w;
        for (w = 0; w < width - 5; w += 6) {
            READ_PIXELS(u, y, v);
            READ_PIXELS(y, u, y);
            READ_PIXELS(v, y, u);
            READ_PIXELS(y, v, y);
        }
        if (w < width - 1) {
            READ_PIXELS(u, y, v);

            val  = av_le2ne32(*src++);
            *y++ =  val & 0x3FF;
        }
        if (w < width - 3) {
            *u++ = (val >> 10) & 0x3FF;
            *y++ = (val >> 20) & 0x3FF;

            val  = av_le2ne32(*src++);
            *v++ =  val & 0x3FF;
            *y++ = (val >> 10) & 0x3FF;
        }

        bytes += stride;
    }
}