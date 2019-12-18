#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsInt32Number ;
struct TYPE_6__ {double X; double Y; double Z; } ;
struct TYPE_5__ {double X; double Y; double Z; } ;
struct TYPE_7__ {int IlluminantType; TYPE_2__ SurroundXYZ; TYPE_1__ IlluminantXYZ; } ;
typedef  TYPE_3__ cmsICCViewingConditions ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodVal (char*,double,double,double) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigViewingConditionsTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static
cmsInt32Number CheckICCViewingConditions(cmsInt32Number Pass,  cmsHPROFILE hProfile)
{
    cmsICCViewingConditions* v;
    cmsICCViewingConditions  s;

    switch (Pass) {

        case 1:
            s.IlluminantType = 1;
            s.IlluminantXYZ.X = 0.1;
            s.IlluminantXYZ.Y = 0.2;
            s.IlluminantXYZ.Z = 0.3;
            s.SurroundXYZ.X = 0.4;
            s.SurroundXYZ.Y = 0.5;
            s.SurroundXYZ.Z = 0.6;

            if (!cmsWriteTag(DbgThread(), hProfile, cmsSigViewingConditionsTag, &s)) return 0;
            return 1;

        case 2:
            v = (cmsICCViewingConditions *) cmsReadTag(DbgThread(), hProfile, cmsSigViewingConditionsTag);
            if (v == NULL) return 0;

            if (v ->IlluminantType != 1) return 0;
            if (!IsGoodVal("IlluminantXYZ.X", v ->IlluminantXYZ.X, 0.1, 0.001)) return 0;
            if (!IsGoodVal("IlluminantXYZ.Y", v ->IlluminantXYZ.Y, 0.2, 0.001)) return 0;
            if (!IsGoodVal("IlluminantXYZ.Z", v ->IlluminantXYZ.Z, 0.3, 0.001)) return 0;

            if (!IsGoodVal("SurroundXYZ.X", v ->SurroundXYZ.X, 0.4, 0.001)) return 0;
            if (!IsGoodVal("SurroundXYZ.Y", v ->SurroundXYZ.Y, 0.5, 0.001)) return 0;
            if (!IsGoodVal("SurroundXYZ.Z", v ->SurroundXYZ.Z, 0.6, 0.001)) return 0;

            return 1;

        default:
            return 0;
    }

}