#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int i_extra; scalar_t__ p_extra; } ;
typedef  TYPE_1__ es_format_t ;

/* Variables and functions */

bool hevc_get_profile_level(const es_format_t *p_fmt, uint8_t *pi_profile,
                            uint8_t *pi_level, uint8_t *pi_nal_length_size)
{
    const uint8_t *p = (const uint8_t*)p_fmt->p_extra;
    if(p_fmt->i_extra < 23 || p[0] != 1)
        return false;

    /* HEVCDecoderConfigurationRecord */
    if(pi_profile)
        *pi_profile = p[1] & 0x1F;

    if(pi_level)
        *pi_level = p[12];

    if (pi_nal_length_size)
        *pi_nal_length_size = 1 + (p[21]&0x03);

    return true;
}