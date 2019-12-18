#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_4__ {double L; double a; double b; double X; double Y; double Z; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ cmsCIEXYZ ;
typedef  TYPE_1__ cmsCIELab ;

/* Variables and functions */
 int Verbose ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ hTransLab ; 
 scalar_t__ hTransXYZ ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double,double,double) ; 

__attribute__((used)) static
void PrintPCSFloat(cmsContext ContextID, cmsFloat64Number Input[])
{
    if (Verbose > 1 && hTransXYZ && hTransLab) {

        cmsCIEXYZ XYZ = { 0, 0, 0 };
        cmsCIELab Lab = { 0, 0, 0 };

        if (hTransXYZ) cmsDoTransform(ContextID, hTransXYZ, Input, &XYZ, 1);
        if (hTransLab) cmsDoTransform(ContextID, hTransLab, Input, &Lab, 1);

        printf("[PCS] Lab=(%.4f,%.4f,%.4f) XYZ=(%.4f,%.4f,%.4f)\n", Lab.L, Lab.a, Lab.b,
            XYZ.X * 100.0, XYZ.Y * 100.0, XYZ.Z * 100.0);

    }
}