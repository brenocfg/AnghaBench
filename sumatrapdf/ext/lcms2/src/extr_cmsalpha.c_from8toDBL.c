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
typedef  double cmsUInt8Number ;
typedef  double cmsFloat64Number ;

/* Variables and functions */

__attribute__((used)) static
void from8toDBL(void* dst, const void* src)
{
       *(cmsFloat64Number*)dst = (*(cmsUInt8Number*)src) / 255.0;
}