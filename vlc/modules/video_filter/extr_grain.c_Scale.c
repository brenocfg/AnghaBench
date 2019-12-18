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
typedef  int int16_t ;

/* Variables and functions */
 int BANK_SIZE ; 

__attribute__((used)) static void Scale(int16_t *dst, int16_t *src, int scale)
{
    const int N = BANK_SIZE;
    const int shift = 7 + 8;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            const int v = src[y * N + x];
            int vq;
            if (v >= 0)
                vq =   ( v * scale + (1 << (shift-1)) - 1) >> shift;
            else
                vq = -((-v * scale + (1 << (shift-1)) - 1) >> shift);
            dst[y * N + x] = vq;
        }
    }
}