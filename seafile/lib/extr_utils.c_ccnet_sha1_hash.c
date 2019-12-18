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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t
ccnet_sha1_hash (const void *v)
{
    /* 31 bit hash function */
    const unsigned char *p = v;
    uint32_t h = 0;
    int i;

    for (i = 0; i < 20; i++)
        h = (h << 5) - h + p[i];

    return h;
}