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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void SparseCopy( int16_t *p_dest, const int16_t *p_src,
                        size_t i_nb_samples, size_t i_offset, size_t i_stride )
{
    for ( size_t i = 0; i < i_nb_samples; i++ )
    {
        p_dest[2 * i] = p_src[i_offset];
        p_dest[2 * i + 1] = p_src[i_offset + 1];
        i_offset += 2 * i_stride;
    }
}