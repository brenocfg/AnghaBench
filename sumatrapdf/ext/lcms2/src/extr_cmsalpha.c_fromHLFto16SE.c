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
typedef  float cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_ENDIAN (int /*<<< orphan*/ ) ; 
 float _cmsHalf2Float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsQuickSaturateWord (float) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void const*) ; 

__attribute__((used)) static
void fromHLFto16SE(void* dst, const void* src)
{
#ifndef CMS_NO_HALF_SUPPORT
    cmsFloat32Number n = _cmsHalf2Float(*(cmsUInt16Number*)src);
    cmsUInt16Number i = _cmsQuickSaturateWord(n * 65535.0f);
    *(cmsUInt16Number*)dst = CHANGE_ENDIAN(i);
#else
    cmsUNUSED_PARAMETER(dst);
    cmsUNUSED_PARAMETER(src);
#endif
}