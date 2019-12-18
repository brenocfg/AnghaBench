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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

void Merge16BitGeneric( void *_p_dest, const void *_p_s1,
                        const void *_p_s2, size_t i_bytes )
{
    uint16_t *p_dest = _p_dest;
    const uint16_t *p_s1 = _p_s1;
    const uint16_t *p_s2 = _p_s2;

    for( size_t i_words = i_bytes / 2; i_words > 0; i_words-- )
        *p_dest++ = ( *p_s1++ + *p_s2++ ) >> 1;
}