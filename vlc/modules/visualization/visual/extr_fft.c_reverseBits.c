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

/* Variables and functions */
 unsigned int FFT_BUFFER_SIZE_LOG ; 

__attribute__((used)) static int reverseBits(unsigned int initial)
{
    unsigned int reversed = 0, loop;
    for(loop = 0; loop < FFT_BUFFER_SIZE_LOG; loop++) {
        reversed <<= 1;
        reversed += (initial & 1);
        initial >>= 1;
    }
    return reversed;
}