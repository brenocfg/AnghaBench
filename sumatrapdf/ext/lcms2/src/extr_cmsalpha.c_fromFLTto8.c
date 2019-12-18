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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  float cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsQuickSaturateByte (float) ; 

__attribute__((used)) static
void fromFLTto8(void* dst, const void* src)
{
    cmsFloat32Number n = *(cmsFloat32Number*)src;
    *(cmsUInt8Number*)dst = _cmsQuickSaturateByte(n * 255.0f);
}