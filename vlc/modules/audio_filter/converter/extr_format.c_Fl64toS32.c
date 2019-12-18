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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_4__ {int i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lround (float) ; 

__attribute__((used)) static block_t *Fl64toS32(filter_t *filter, block_t *b)
{
    double  *src = (double *)b->p_buffer;
    int32_t *dst = (int32_t *)src;
    for (size_t i = b->i_buffer / 8; i--;)
    {
        float s = *(src++) * 2147483648.;
        if (s >= 2147483647.f)
            *(dst++) = 2147483647;
        else
        if (s <= -2147483648.f)
            *(dst++) = -2147483648;
        else
            *(dst++) = lround(s);
    }
    VLC_UNUSED(filter);
    return b;
}