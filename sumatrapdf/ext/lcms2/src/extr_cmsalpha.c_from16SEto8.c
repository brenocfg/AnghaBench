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
 int /*<<< orphan*/  FROM_16_TO_8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void from16SEto8(void* dst, const void* src)
{
    cmsUInt16Number n = *(cmsUInt16Number*)src;
    *(cmsUInt8Number*)dst = FROM_16_TO_8(CHANGE_ENDIAN(n));
}