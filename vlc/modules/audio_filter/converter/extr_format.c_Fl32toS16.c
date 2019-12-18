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
typedef  int int32_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_4__ {int i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int lroundf (float) ; 

__attribute__((used)) static block_t *Fl32toS16(filter_t *filter, block_t *b)
{
    VLC_UNUSED(filter);
    float   *src = (float *)b->p_buffer;
    int16_t *dst = (int16_t *)src;
    for (int i = b->i_buffer / 4; i--;) {
#if 0
        /* Slow version. */
        if (*src >= 1.0) *dst = 32767;
        else if (*src < -1.0) *dst = -32768;
        else *dst = lroundf(*src * 32768.f);
        src++; dst++;
#else
        /* This is Walken's trick based on IEEE float format. */
        union { float f; int32_t i; } u;
        u.f = *src++ + 384.f;
        if (u.i > 0x43c07fff)
            *dst++ = 32767;
        else if (u.i < 0x43bf8000)
            *dst++ = -32768;
        else
            *dst++ = u.i - 0x43c00000;
#endif
    }
    b->i_buffer /= 2;
    return b;
}