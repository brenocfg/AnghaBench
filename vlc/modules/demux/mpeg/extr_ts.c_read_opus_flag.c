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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int16_t read_opus_flag(uint8_t **buf, size_t *len)
{
    if (*len < 2)
        return -1;

    int16_t ret = ((*buf)[0] << 8) | (*buf)[1];

    *len -= 2;
    *buf += 2;

    if (ret & (3<<13))
        ret = -1;

    return ret;
}