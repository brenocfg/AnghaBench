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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline void rtcp_fb_nack_set_range_extra(uint8_t *p_rtcp_fb_nack,
                                                 uint16_t extra)
{
    p_rtcp_fb_nack[2] = (extra >> 8) & 0xff;
    p_rtcp_fb_nack[3] = extra & 0xff;
}