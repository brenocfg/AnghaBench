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
typedef  int cmsUInt32Number ;
typedef  int cmsUInt16Number ;

/* Variables and functions */

__attribute__((used)) static
cmsUInt16Number Fn8D3(cmsUInt16Number a1, cmsUInt16Number a2, cmsUInt16Number a3, cmsUInt16Number a4,
                      cmsUInt16Number a5, cmsUInt16Number a6, cmsUInt16Number a7, cmsUInt16Number a8,
                      cmsUInt32Number m)
{
    return (cmsUInt16Number) ((3*a1 + 2*a2 + 3*a3 + a4 + a5 + a6 + a7 + a8) / (m + 5));
}