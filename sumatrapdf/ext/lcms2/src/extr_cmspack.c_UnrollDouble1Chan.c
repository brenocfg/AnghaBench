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
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsQuickSaturateWord (double) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollDouble1Chan(cmsContext ContextID, register _cmsTRANSFORM* info,
                                  register cmsUInt16Number wIn[],
                                  register cmsUInt8Number* accum,
                                  register cmsUInt32Number Stride)
{
    cmsFloat64Number* Inks = (cmsFloat64Number*) accum;

    wIn[0] = wIn[1] = wIn[2] = _cmsQuickSaturateWord(Inks[0] * 65535.0);

    return accum + sizeof(cmsFloat64Number);

    cmsUNUSED_PARAMETER(info);
    cmsUNUSED_PARAMETER(Stride);
}