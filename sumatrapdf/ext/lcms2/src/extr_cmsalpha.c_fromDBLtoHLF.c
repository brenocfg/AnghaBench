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
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFloat2Half (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void const*) ; 

__attribute__((used)) static
void fromDBLtoHLF(void* dst, const void* src)
{
#ifndef CMS_NO_HALF_SUPPORT
       cmsFloat32Number n = (cmsFloat32Number) *(cmsFloat64Number*)src;
       *(cmsUInt16Number*)dst = _cmsFloat2Half(n);
#else
    cmsUNUSED_PARAMETER(dst);
    cmsUNUSED_PARAMETER(src);
#endif
}