#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
typedef  int /*<<< orphan*/  cmsCIELab ;
struct TYPE_5__ {int L; scalar_t__ h; scalar_t__ C; } ;
typedef  TYPE_1__ cmsCIELCh ;
struct TYPE_6__ {int Contrast; int Brightness; int /*<<< orphan*/  WPdest; int /*<<< orphan*/  WPsrc; scalar_t__ lAdjustWP; scalar_t__ Hue; scalar_t__ Saturation; } ;
typedef  TYPE_2__* LPBCHSWADJUSTS ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  cmsFloat2LabEncoded (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsLCh2Lab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsLab2LCh (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsLab2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsLabEncoded2Float (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cmsXYZ2Lab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int bchswSampler(cmsContext ContextID, register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void* Cargo)
{
    cmsCIELab LabIn, LabOut;
    cmsCIELCh LChIn, LChOut;
    cmsCIEXYZ XYZ;
    LPBCHSWADJUSTS bchsw = (LPBCHSWADJUSTS) Cargo;


    cmsLabEncoded2Float(ContextID, &LabIn, In);


    cmsLab2LCh(ContextID, &LChIn, &LabIn);

    // Do some adjusts on LCh

    LChOut.L = LChIn.L * bchsw ->Contrast + bchsw ->Brightness;
    LChOut.C = LChIn.C + bchsw -> Saturation;
    LChOut.h = LChIn.h + bchsw -> Hue;


    cmsLCh2Lab(ContextID, &LabOut, &LChOut);

    // Move white point in Lab
    if (bchsw->lAdjustWP) {
           cmsLab2XYZ(ContextID, &bchsw->WPsrc, &XYZ, &LabOut);
           cmsXYZ2Lab(ContextID, &bchsw->WPdest, &LabOut, &XYZ);
    }

    // Back to encoded

    cmsFloat2LabEncoded(ContextID, Out, &LabOut);

    return TRUE;
}