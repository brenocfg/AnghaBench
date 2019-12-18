#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsInt32Number ;
typedef  int cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsCIExyY ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
struct TYPE_6__ {int L; int a; int b; } ;
typedef  TYPE_1__ cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int cmsDeltaE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsLab2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsXYZ2Lab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsXYZ2xyY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsxyY2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckLab2xyY(void)
{
    cmsInt32Number l, a, b;
    cmsFloat64Number dist, Max = 0;
    cmsCIELab Lab, Lab2;
    cmsCIEXYZ XYZ;
    cmsCIExyY xyY;

    for (l=0; l <= 100; l += 10) {

        for (a=-128; a <= +128; a += 8) {

            for (b=-128; b <= 128; b += 8) {

                Lab.L = l;
                Lab.a = a;
                Lab.b = b;

                cmsLab2XYZ(DbgThread(), NULL, &XYZ, &Lab);
                cmsXYZ2xyY(DbgThread(), &xyY, &XYZ);
                cmsxyY2XYZ(DbgThread(), &XYZ, &xyY);
                cmsXYZ2Lab(DbgThread(), NULL, &Lab2, &XYZ);

                dist = cmsDeltaE(DbgThread(), &Lab, &Lab2);
                if (dist > Max) Max = dist;

            }
        }
    }

    return Max < 1E-12;
}