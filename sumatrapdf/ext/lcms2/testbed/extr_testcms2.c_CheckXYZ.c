#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
struct TYPE_3__ {double X; double Y; double Z; } ;
typedef  TYPE_1__ cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodFixed15_16 (char*,double,double) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
cmsInt32Number CheckXYZ(cmsInt32Number Pass, cmsHPROFILE hProfile, cmsTagSignature tag)
{
    cmsCIEXYZ XYZ, *Pt;


    switch (Pass) {

        case 1:

            XYZ.X = 1.0; XYZ.Y = 1.1; XYZ.Z = 1.2;
            return cmsWriteTag(DbgThread(), hProfile, tag, &XYZ);

        case 2:
            Pt = (cmsCIEXYZ *) cmsReadTag(DbgThread(), hProfile, tag);
            if (Pt == NULL) return 0;
            return IsGoodFixed15_16("X", 1.0, Pt ->X) &&
                   IsGoodFixed15_16("Y", 1.1, Pt->Y) &&
                   IsGoodFixed15_16("Z", 1.2, Pt -> Z);

        default:
            return 0;
    }
}