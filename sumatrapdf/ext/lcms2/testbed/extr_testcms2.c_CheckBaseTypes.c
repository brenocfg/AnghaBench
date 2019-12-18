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
typedef  int /*<<< orphan*/  cmsUInt64Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsU8Fixed8Number ;
typedef  int /*<<< orphan*/  cmsU16Fixed16Number ;
typedef  int /*<<< orphan*/  cmsSignature ;
typedef  int /*<<< orphan*/  cmsS15Fixed16Number ;
typedef  int /*<<< orphan*/  cmsInt8Number ;
typedef  int /*<<< orphan*/  cmsInt64Number ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsInt16Number ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsFloat32Number ;

/* Variables and functions */

__attribute__((used)) static
cmsInt32Number CheckBaseTypes(void)
{
    // Ignore warnings about conditional expression
#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

    if (sizeof(cmsUInt8Number) != 1) return 0;
    if (sizeof(cmsInt8Number) != 1) return 0;
    if (sizeof(cmsUInt16Number) != 2) return 0;
    if (sizeof(cmsInt16Number) != 2) return 0;
    if (sizeof(cmsUInt32Number) != 4) return 0;
    if (sizeof(cmsInt32Number) != 4) return 0;
    if (sizeof(cmsUInt64Number) != 8) return 0;
    if (sizeof(cmsInt64Number) != 8) return 0;
    if (sizeof(cmsFloat32Number) != 4) return 0;
    if (sizeof(cmsFloat64Number) != 8) return 0;
    if (sizeof(cmsSignature) != 4) return 0;
    if (sizeof(cmsU8Fixed8Number) != 2) return 0;
    if (sizeof(cmsS15Fixed16Number) != 4) return 0;
    if (sizeof(cmsU16Fixed16Number) != 4) return 0;

    return 1;
}