#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_4__ {unsigned int i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */

__attribute__((used)) static block_t *Process (filter_t *filter, block_t *block)
{
    const float factor = .70710678 /* 1. / sqrtf (2) */;
    float *spl = (float *)block->p_buffer;

    for (unsigned i = block->i_nb_samples; i > 0; i--)
    {
        float s = (spl[0] - spl[1]) * factor;

        *(spl++) = s;
        *(spl++) = s;
        /* TODO: set output format to mono */
    }
    (void) filter;
    return block;
}