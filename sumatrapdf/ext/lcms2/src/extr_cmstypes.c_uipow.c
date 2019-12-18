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
typedef  scalar_t__ cmsUInt32Number ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 

__attribute__((used)) static
cmsUInt32Number uipow(cmsUInt32Number n, cmsUInt32Number a, cmsUInt32Number b)
{
    cmsUInt32Number rv = 1, rc;

    if (a == 0) return 0;
    if (n == 0) return 0;

    for (; b > 0; b--) {

        rv *= a;

        // Check for overflow
        if (rv > UINT_MAX / a) return (cmsUInt32Number) -1;

    }

    rc = rv * n;

    if (rv != rc / n) return (cmsUInt32Number) -1;
    return rc;
}