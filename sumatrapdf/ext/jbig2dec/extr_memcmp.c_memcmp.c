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

int
memcmp(const void *b1, const void *b2, size_t len)
{
    unsigned char *a, *b;
    size_t i;

    a = (unsigned char *)b1;
    b = (unsigned char *)b2;
    for (i = 0; i < len; i++) {
        if (*a != *b) {
            /* strings differ */
            return (*a < *b) ? -1 : 1;
        }
        a++;
        b++;
    }

    /* strings match */
    return 0;
}