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
struct TYPE_6__ {int L; int a; int b; } ;
typedef  TYPE_1__ cmsCIELab ;
typedef  int /*<<< orphan*/  cmsCIELCh ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int cmsDeltaE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsLCh2Lab (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsLab2LCh (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static
cmsInt32Number CheckLab2LCh(void)
{
    cmsInt32Number l, a, b;
    cmsFloat64Number dist, Max = 0;
    cmsCIELab Lab, Lab2;
    cmsCIELCh LCh;

    for (l=0; l <= 100; l += 10) {

        for (a=-128; a <= +128; a += 8) {

            for (b=-128; b <= 128; b += 8) {

                Lab.L = l;
                Lab.a = a;
                Lab.b = b;

                cmsLab2LCh(DbgThread(), &LCh, &Lab);
                cmsLCh2Lab(DbgThread(), &Lab2, &LCh);

                dist = cmsDeltaE(DbgThread(), &Lab, &Lab2);
                if (dist > Max) Max = dist;
            }
        }
    }

    return Max < 1E-12;
}