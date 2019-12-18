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
typedef  int /*<<< orphan*/  cmsUInt16Number ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_ENDIAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FROM_8_TO_16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void from8to16SE(void* dst, const void* src)
{
    cmsUInt8Number n = *(cmsUInt8Number*)src;
    *(cmsUInt16Number*)dst = CHANGE_ENDIAN(FROM_8_TO_16(n));
}