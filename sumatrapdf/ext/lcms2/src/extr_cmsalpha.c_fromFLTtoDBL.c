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
typedef  scalar_t__ cmsFloat64Number ;
typedef  scalar_t__ cmsFloat32Number ;

/* Variables and functions */

__attribute__((used)) static
void fromFLTtoDBL(void* dst, const void* src)
{
    cmsFloat32Number n = *(cmsFloat32Number*)src;
    *(cmsFloat64Number*)dst = (cmsFloat64Number)n;
}