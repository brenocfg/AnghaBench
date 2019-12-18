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
typedef  unsigned int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned xiph_CountHeaders(const void *p_extra, unsigned i_extra)
{
    const uint8_t *p = (const uint8_t*) p_extra;
    if (!i_extra)
        return 0;
    /* First byte is headers count */
    if(1U + *p > i_extra)
        return 0;
    return *p + 1;
}