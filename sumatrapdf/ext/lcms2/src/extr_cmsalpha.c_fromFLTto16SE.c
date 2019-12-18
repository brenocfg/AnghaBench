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
 int /*<<< orphan*/  _cmsQuickSaturateWord (float) ; 

__attribute__((used)) static
void fromFLTto16SE(void* dst, const void* src)
{
    cmsFloat32Number n = *(cmsFloat32Number*)src;
    cmsUInt16Number i = _cmsQuickSaturateWord(n * 65535.0f);

    *(cmsUInt16Number*)dst = CHANGE_ENDIAN(i);
}