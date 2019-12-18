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
ccnet_sha1_equal (const void *v1,
                  const void *v2)
{
    const unsigned char *p1 = v1;
    const unsigned char *p2 = v2;
    int i;

    for (i = 0; i < 20; i++)
        if (p1[i] != p2[i])
            return 0;
    
    return 1;
}