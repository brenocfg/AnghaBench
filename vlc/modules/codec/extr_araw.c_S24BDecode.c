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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void S24BDecode( void *outp, const uint8_t *in, unsigned samples )
{
    uint32_t *out = outp;

    for( size_t i = 0; i < samples; i++ )
    {
        uint32_t s = ((in[0] << 24) | (in[1] << 16) | (in[2] << 8));
        *(out++) = s;
        in += 3;
    }
}