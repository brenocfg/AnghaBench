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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodVal (char*,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsEstimateGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cmsFreeToneCurveTriple (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigVcgtTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static
cmsInt32Number CheckVCGT(cmsInt32Number Pass,  cmsHPROFILE hProfile)
{
    cmsToneCurve* Curves[3];
    cmsToneCurve** PtrCurve;

     switch (Pass) {

        case 1:
            Curves[0] = cmsBuildGamma(DbgThread(), 1.1);
            Curves[1] = cmsBuildGamma(DbgThread(), 2.2);
            Curves[2] = cmsBuildGamma(DbgThread(), 3.4);

            if (!cmsWriteTag(DbgThread(), hProfile, cmsSigVcgtTag, Curves)) return 0;

            cmsFreeToneCurveTriple(DbgThread(), Curves);
            return 1;


        case 2:

             PtrCurve = (cmsToneCurve **) cmsReadTag(DbgThread(), hProfile, cmsSigVcgtTag);
             if (PtrCurve == NULL) return 0;
             if (!IsGoodVal("VCGT R", cmsEstimateGamma(DbgThread(), PtrCurve[0], 0.01), 1.1, 0.001)) return 0;
             if (!IsGoodVal("VCGT G", cmsEstimateGamma(DbgThread(), PtrCurve[1], 0.01), 2.2, 0.001)) return 0;
             if (!IsGoodVal("VCGT B", cmsEstimateGamma(DbgThread(), PtrCurve[2], 0.01), 3.4, 0.001)) return 0;
             return 1;

        default:;
    }

    return 0;
}