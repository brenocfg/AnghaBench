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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  scalar_t__ cmsFloat64Number ;

/* Variables and functions */
 scalar_t__ _cmsHalf2Float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void const*) ; 

__attribute__((used)) static
void fromHLFtoDBL(void* dst, const void* src)
{
#ifndef CMS_NO_HALF_SUPPORT
       *(cmsFloat64Number*)dst = (cmsFloat64Number)_cmsHalf2Float(*(cmsUInt16Number*)src);
#else
    cmsUNUSED_PARAMETER(dst);
    cmsUNUSED_PARAMETER(src);
#endif
}