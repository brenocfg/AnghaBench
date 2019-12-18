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
typedef  void uint8_t ;

/* Variables and functions */

__attribute__((used)) static void *adjust_pointer(const void *p, void *old_base, size_t sz, void *new_base) {

        if (!p)
                return NULL;

        if (old_base == new_base)
                return (void*) p;

        if ((uint8_t*) p < (uint8_t*) old_base)
                return (void*) p;

        if ((uint8_t*) p >= (uint8_t*) old_base + sz)
                return (void*) p;

        return (uint8_t*) new_base + ((uint8_t*) p - (uint8_t*) old_base);
}