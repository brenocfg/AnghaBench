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
typedef  int uint64_t ;

/* Variables and functions */
 int UINT64_MAX ; 

uint64_t lpDecodeBacklen(unsigned char *p) {
    uint64_t val = 0;
    uint64_t shift = 0;
    do {
        val |= (uint64_t)(p[0] & 127) << shift;
        if (!(p[0] & 128)) break;
        shift += 7;
        p--;
        if (shift > 28) return UINT64_MAX;
    } while(1);
    return val;
}