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

/* Variables and functions */

__attribute__((used)) static uint8_t odd_min9_is_prime(size_t value)
{
    size_t i = 3;

    while (i * i <= value) {
        if (!(value % i))
            return 0;

        i += 2;
    }

    return 1;
}