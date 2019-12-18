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
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsIsToneCurveLinear (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckGamma(cmsInt32Number Pass, cmsHPROFILE hProfile, cmsTagSignature tag)
{
    cmsToneCurve *g, *Pt;
    cmsInt32Number rc;

    switch (Pass) {

        case 1:

            g = cmsBuildGamma(DbgThread(), 1.0);
            rc = cmsWriteTag(DbgThread(), hProfile, tag, g);
            cmsFreeToneCurve(DbgThread(), g);
            return rc;

        case 2:
            Pt = (cmsToneCurve *) cmsReadTag(DbgThread(), hProfile, tag);
            if (Pt == NULL) return 0;
            return cmsIsToneCurveLinear(DbgThread(), Pt);

        default:
            return 0;
    }
}