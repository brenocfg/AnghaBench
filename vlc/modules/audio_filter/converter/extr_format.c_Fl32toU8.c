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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_4__ {int i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ lroundf (float) ; 

__attribute__((used)) static block_t *Fl32toU8(filter_t *filter, block_t *b)
{
    float   *src = (float *)b->p_buffer;
    uint8_t *dst = (uint8_t *)src;
    for (size_t i = b->i_buffer / 4; i--;)
    {
        float s = *(src++) * 128.f;
        if (s >= 127.f)
            *(dst++) = 255;
        else
        if (s <= -128.f)
            *(dst++) = 0;
        else
            *(dst++) = lroundf(s) + 128;
    }
    b->i_buffer /= 4;
    VLC_UNUSED(filter);
    return b;
}