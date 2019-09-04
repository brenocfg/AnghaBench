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

/* Variables and functions */
 unsigned int ZIPMAP_BIGLEN ; 

__attribute__((used)) static unsigned long zipmapRequiredLength(unsigned int klen, unsigned int vlen) {
    unsigned int l;

    l = klen+vlen+3;
    if (klen >= ZIPMAP_BIGLEN) l += 4;
    if (vlen >= ZIPMAP_BIGLEN) l += 4;
    return l;
}