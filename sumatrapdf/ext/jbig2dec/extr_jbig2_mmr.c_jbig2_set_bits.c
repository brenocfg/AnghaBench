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
typedef  int byte ;

/* Variables and functions */
 int* lm ; 
 int* rm ; 

__attribute__((used)) static void
jbig2_set_bits(byte *line, uint32_t x0, uint32_t x1)
{
    uint32_t a0, a1, b0, b1, a;

    a0 = x0 >> 3;
    a1 = x1 >> 3;

    b0 = x0 & 7;
    b1 = x1 & 7;

    if (a0 == a1) {
        line[a0] |= lm[b0] & rm[b1];
    } else {
        line[a0] |= lm[b0];
        for (a = a0 + 1; a < a1; a++)
            line[a] = 0xFF;
        if (b1)
            line[a1] |= rm[b1];
    }
}