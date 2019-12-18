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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int U16_AT (int const*) ; 
 int U32_AT (int const*) ; 

__attribute__((used)) static void S20BDecode( void *outp, const uint8_t *in, unsigned samples )
{
    int32_t *out = outp;

    while( samples >= 2 )
    {
        uint32_t dw = U32_AT(in);
        in += 4;
        *(out++) = dw & ~0xFFF;
        *(out++) = (dw << 20) | (*in << 12);
        in++;
        samples -= 2;
    }

    /* No U32_AT() for the last odd sample: avoid off-by-one overflow! */
    if( samples )
        *(out++) = (U16_AT(in) << 16) | ((in[2] & 0xF0) << 8);
}