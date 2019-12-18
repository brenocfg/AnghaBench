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
typedef  int /*<<< orphan*/ * cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_8_TO_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FomLabV2ToLabV4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollALabV2_8(cmsContext ContextID, register _cmsTRANSFORM* info,
                               register cmsUInt16Number wIn[],
                               register cmsUInt8Number* accum,
                               register cmsUInt32Number Stride)
{
    accum++;  // A
    wIn[0] = FomLabV2ToLabV4(FROM_8_TO_16(*accum)); accum++;     // L
    wIn[1] = FomLabV2ToLabV4(FROM_8_TO_16(*accum)); accum++;     // a
    wIn[2] = FomLabV2ToLabV4(FROM_8_TO_16(*accum)); accum++;     // b

    return accum;

    cmsUNUSED_PARAMETER(info);
    cmsUNUSED_PARAMETER(Stride);
}