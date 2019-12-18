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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void blur_line_c(uint16_t *dc, uint16_t *buf, uint16_t *buf1,
                        uint8_t *src, int sstride, int width)
{
    for( int x = 0; x < width; x++ ) {
        int v = buf1[x] + src[2*x] + src[2*x+1] + src[2*x+sstride] +
                src[2*x+1+sstride];
        int old = buf[x];
        buf[x] = v;
        dc[x] = v - old;
    }
}